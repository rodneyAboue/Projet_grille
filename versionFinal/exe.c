#include "gen_graph.h"
#include <string.h>
#include "entree_kml.h"
#include "dislin.h"


#define distanceVoisinCreation 0.001

int main(int argc, char* argv[]){
	// Vérification des arguments
	if(argc < 2){
		printf("Erreur argument: ./exe export.kml\n");
		return 1;
	}

	// Variables
	liste_polygone* listeDepart = init_liste_polygone();
	pointp* sommetDepart;
	pointp* sommetEnCours;

	int nbPoly = 0;
	polygone** listePolygone = (polygone**)malloc(nbPoly*sizeof(polygone*));

	// Extraction du fichier KML
	sommetDepart = extraire_polygones(argv[1], listeDepart);

	// Vérification de l'export et mise en place dans les structures polygones
	if(sommetDepart != NULL){
		// Récupération de l'ensemble des polygones
		liste_polygone* liste = listeDepart;
		//Le premier élément de la listePolygone étant vide, on passe directement au second
		while(liste->next != NULL){
			liste = liste->next;
			sommetDepart = liste->polygone->next;
			if(sommetDepart->next != NULL){
				sommetEnCours = sommetDepart;
				while(sommetEnCours->next != NULL){
					sommetEnCours = sommetEnCours->next;
				}
				sommetEnCours->next = sommetDepart;
				listePolygone = (polygone**)realloc(listePolygone, ++(nbPoly)*sizeof(polygone*));
				listePolygone[nbPoly-1] = creerPoly(sommetDepart);
			}
		}

	}else{
		printf("Erreur extraction, fichier vide ou incorrect \n");
		return 1;
	}

	if(nbPoly == 0){
		printf("Problème lors de l'extraction, ou Polygone à un seul point \n");
		return 1;
	}else{
		if(gen_point_polygone(listePolygone[0], listePolygone[0]->sommetPoly, distanceVoisinCreation)){
			for(int i = 1; i < nbPoly; i++){
				delete_point_polygone(listePolygone[0], listePolygone[i]);
			}
			genererGraphe(listeDepart, listePolygone[0]);
		}else{
			printf("Génération impossible, point de départ en dehors du polygone \n");
		}
	}
	printf("Graphe généré dans tspp.dat \n");

	//system("/opt/ibm/ILOG/CPLEX_Studio126/opl/bin/x86-64_linux/oplrun tspp.mod tspp.dat params.dat");


	FILE* fichier = fopen("solutions.res","r");

	if(fichier == NULL){
		perror("fopen");
		exit(-1);
	}
	else{
		int nb_sommets_chemin,nb_points_couverts,id_point;
		double longueur_chemin;

		liste_polygone* liste = init_liste_polygone();	
		pointp* depart, *visites = NULL, *visites_next, *vus = NULL, *vus_next, *non_vus = NULL, *non_vus_next;


		depart = extraire_polygones( "test_io_export.kml", liste);
		puts("entree : ok\n");

		while(fscanf(fichier, "%d %lf", &nb_sommets_chemin,&longueur_chemin) != EOF){
			printf("CHEMIN :\n%d sommets\nlongueur = %f\n\n", nb_sommets_chemin,longueur_chemin);

			for(int i = 1; i <= nb_sommets_chemin; i++){
				fscanf(fichier,"%d", &id_point);
				printf("sommet %d\n", id_point);

				visites_next = visites;				
				while(visites_next != NULL){
							
					visites_next = visites_next->next;					
				}
				visites_next = listePolygone[0]->listePointPoly[i];
				visites_next->next = NULL;
											
								
				listePolygone[0]->listePointPoly[i]->etat = 'x';
			}

			fscanf(fichier,"%d", &nb_points_couverts);

			printf("\nliste des %d points couverts :\n", nb_points_couverts);

			for(int j = 1; j <= nb_points_couverts; j++){
				fscanf(fichier,"%d ", &id_point);
				printf("point couvert d'id %d\n", id_point);


				for(int k = 0; k < listePolygone[0]->nbPoint; k++){
					if(listePolygone[0]->listePointPoly[k]->id == id_point && listePolygone[0]->listePointPoly[k]->etat !='o' && listePolygone[0]->listePointPoly[k]->etat != 'x'){ // 'o' = "vu"    'x' = "visité"
						vus_next = vus;				
						while(vus_next != NULL){
							
							vus_next = vus_next->next;					
						}
						vus_next = listePolygone[0]->listePointPoly[k];
						vus_next->next = NULL;
											
								
						listePolygone[0]->listePointPoly[k]->etat = 'o';					
					}
										
				}
			}

			for(int l = 0; l < listePolygone[0]->nbPoint; l++){
					if(listePolygone[0]->listePointPoly[l]->id == id_point && listePolygone[0]->listePointPoly[l]->etat != 'o' && listePolygone[0]->listePointPoly[l]->etat != '.' && listePolygone[0]->listePointPoly[l]->etat != 'x'){ // '.' = "non vu"      'o' = "vu"      'x' = "visité"
						non_vus_next = non_vus;				
						while(non_vus_next != NULL){
							
							non_vus_next = non_vus_next->next;					
						}
						non_vus_next = listePolygone[0]->listePointPoly[l];
						non_vus_next->next = NULL;
											
								
						listePolygone[0]->listePointPoly[l]->etat = '.';					
					}
										
				}
			draw_resultat(liste, visites, vus, non_vus);

			break; 
		}
	}

	
	



	fclose(fichier);



	return 0;
}
