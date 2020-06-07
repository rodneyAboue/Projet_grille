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

	int x = 0;

	FILE* fichier = fopen("solutions.res","r");

	if(fichier == NULL){
		perror("fopen");
		exit(-1);
	}
	else{
		int nb_sommets_chemin,nb_points_couverts,id_point;
		double longueur_chemin;

		pointp *visites = NULL, *visites_last, *visites_next, *vus = NULL, *vus_last,*vus_next, *non_vus = NULL, *non_vus_last, *non_vus_next;
		
		

		puts("entree : ok\n");

		// a chaque itération on lit une ligne (= une solution) du fichier solutions.res
		while(fscanf(fichier, "%d %lf", &nb_sommets_chemin,&longueur_chemin) != EOF){
			printf("CHEMIN :\n%d sommets\nlongueur = %f\n\n", nb_sommets_chemin,longueur_chemin);

			for(int i = 0; i < nb_sommets_chemin; i++){
				fscanf(fichier,"%d", &id_point);
				printf("sommet %d\n", id_point);

				// on ajoute le point à la liste chaînée des points visités		
		
								

				
						
				// dans la liste de points, on cherche le point ayant pour id "id_point" et définit son état comme 'visité'
				for(int z = 0; z < listePolygone[0]->nbPoint; z++)					
					if(listePolygone[0]->listePointPoly[z]->id == id_point){
						//printf("=>sommet %d\n", id_point);
						listePolygone[0]->listePointPoly[z]->etat = 'x'; //'x' = sommet visité
						
						// on ajoute le point à la liste chaînée des points visités
						
		
						visites_next = listePolygone[0]->listePointPoly[z];
				

						if(x++ == 0){ 
							visites = visites_next; 
							visites_last = visites;
						}
						else{
							visites_last->next = visites_next;
							visites_last = visites_last->next;
						}


						break;
			}		}	

			/*if(visites != NULL)*/ visites_last->next = NULL;
				


			int a = 0;int b = 0;

			fscanf(fichier,"%d", &nb_points_couverts);

			printf("\nliste des %d points couverts :\n", nb_points_couverts);

			printf("%d\n",nb_points_couverts);
			for(int j = 1; j <= nb_points_couverts; j++){
				fscanf(fichier,"%d ", &id_point);
				printf("point couvert d'id %d\n", id_point);


				for(int k = 0; k < listePolygone[0]->nbPoint; k++){
					if(listePolygone[0]->listePointPoly[k]->id == id_point && listePolygone[0]->listePointPoly[k]->etat !='o' && listePolygone[0]->listePointPoly[k]->etat != 'x'){ // 'o' = "vu"    'x' = "visité"
						//printf("=>sommet %d\n", id_point);
						listePolygone[0]->listePointPoly[k]->etat = 'o'; //'x' = sommet visité
						
						// on ajoute le point à la liste chaînée des points visités
						
		
						vus_next = listePolygone[0]->listePointPoly[k];
				

						if(a++ == 0){ 
							vus = vus_next; 
							vus_last = vus;
						}
						else{
							vus_last->next = vus_next;
							vus_last = vus_last->next;
						}


						break;


											
										
					
										
				}
			}


			
			

			


			

			for(int l = 0; l < listePolygone[0]->nbPoint; l++){

					if(listePolygone[0]->listePointPoly[l]->id == id_point && listePolygone[0]->listePointPoly[l]->etat != 'o' && listePolygone[0]->listePointPoly[l]->etat != '.' && listePolygone[0]->listePointPoly[l]->etat != 'x'){ // '.' = "non vu"      'o' = "vu"      'x' = "visité"
						
						printf("=>sommet %d\n", id_point);
						listePolygone[0]->listePointPoly[l]->etat = '.'; //'x' = sommet visité
						
						// on ajoute le point à la liste chaînée des points visités
						
		
						non_vus_next = listePolygone[0]->listePointPoly[l];
				

						if(b++ == 0){ 
							printf("8888888\n");
							non_vus = non_vus_next; 
							non_vus_last = non_vus;
						}
						else{
							non_vus_last->next = non_vus_next;
							non_vus_last = non_vus_last->next;
						}


						break;					
						
										
					}
			

			
		}

		


		/*printf("Test de la boucle next\n");

			pointp* sommetActuel = vus;
			for(int j = 0; j <= nb_sommets_chemin; j++){
				printf("sommet id=%d \n", sommetActuel->id);
				sommetActuel = sommetActuel->next;
			}
			printf("Fin du test de la boucle next\n");*/

			


	}printf("xxxxx\n");/*if(vus != NULL)*/ vus_last->next = NULL; if(non_vus != NULL) non_vus_last->next = NULL;


		/*printf("Test de la boucle next\n");

			pointp* sommetActuel = non_vus;
			for(int j = 0; j <= a; j++){
				printf("sommet id=%d \n", sommetActuel->id);
				sommetActuel = sommetActuel->next;
			}
			printf("Fin du test de la boucle next\n");*/

		//printf("\nAAAAAAAAAA\n");

		pointp* entete_vus, *entete_visites, *entete_non_vus;

        entete_vus = init_point_liste_points();
        entete_visites = init_point_liste_points();
        entete_non_vus = init_point_liste_points();

        entete_visites->next = visites;
        entete_vus->next = vus;
        entete_non_vus->next = non_vus;

        afficher_liste_point(entete_visites);
        afficher_liste_point(entete_vus);
        afficher_liste_point(entete_non_vus);
		
	afficher_liste_polygone(listeDepart);

        draw_resultat(listeDepart, entete_visites, entete_vus, entete_non_vus);
        break;
	}}

	
	



	fclose(fichier);



	return 0;
}
