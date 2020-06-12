#include "gen_graph.h"
#include <string.h>
#include "entree_kml.h"
#include "dislin.h"
#include "sortie_pdf.h"

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


	afficher_liste_polygone(listeDepart);	

	printf("\nGraphe généré dans tspp.dat \n");

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
		
		


		// a chaque itération on lit une ligne (= une solution) du fichier solutions.res
		while(fscanf(fichier, "%d %lf", &nb_sommets_chemin,&longueur_chemin) != EOF){
			printf("\nLISTE DES %d SOMMETS DU CHEMIN DE LONGUEUR = %f :\n", nb_sommets_chemin,longueur_chemin);

			
			for(int i = 0; i < nb_sommets_chemin; i++){
				fscanf(fichier,"%d", &id_point);
				

				// on ajoute le point à la liste chaînée des points visités		
		
								

				
						
				// dans la liste de points, on cherche le point ayant pour id "id_point" et définit son état comme 'visité'
				for(int z = 0; z < listePolygone[0]->nbPoint; z++)					
					if(listePolygone[0]->listePointPoly[z]->id == id_point){
						//printf("=>sommet %d\n", id_point);
						listePolygone[0]->listePointPoly[z]->etat = 'x'; //'x' = sommet visité
						
						// on ajoute le point à la liste chaînée des points visités

						printf("sommet %d   x:%f  y:%f\n", id_point, listePolygone[0]->listePointPoly[z]->x,listePolygone[0]->listePointPoly[z]->y );
						
		
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

			visites_last->next = NULL;
				


			int a = 0;int b = 0;

			fscanf(fichier,"%d", &nb_points_couverts);

			printf("\nLISTE DES %d POINTS COUVERTS :\n", nb_points_couverts);

			for(int j = 1; j <= nb_points_couverts; j++){
				fscanf(fichier,"%d ", &id_point);
				


				for(int k = 0; k < listePolygone[0]->nbPoint; k++){
					if(listePolygone[0]->listePointPoly[k]->id == id_point && listePolygone[0]->listePointPoly[k]->etat !='o' && listePolygone[0]->listePointPoly[k]->etat != 'x'){ // 'o' = "vu"    'x' = "visité"
						//printf("=>sommet %d\n", id_point);
						listePolygone[0]->listePointPoly[k]->etat = 'o'; //'o' = sommet vu						
						// on ajoute le point à la liste chaînée des points visités
						
						printf("point %d   x:%f y:%f\n", id_point, listePolygone[0]->listePointPoly[k]->x, listePolygone[0]->listePointPoly[k]->y);
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
						
						printf("point %d   x:%f y:%f\n", id_point, listePolygone[0]->listePointPoly[l]->x, listePolygone[0]->listePointPoly[l]->y);
						listePolygone[0]->listePointPoly[l]->etat = '.'; //'.' = sommet non vu
						
						// on ajoute le point à la liste chaînée des points visités
						
		
						non_vus_next = listePolygone[0]->listePointPoly[l];
				

						if(b++ == 0){ 
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

		


	}vus_last->next = NULL; if(non_vus != NULL) non_vus_last->next = NULL;

		 int nb_points_non_couverts = listePolygone[0]->nbPoint - nb_points_couverts;

		 if(nb_points_non_couverts != 0)
		 	printf("\nLISTE DES %d POINTS NON COUVERTS :\n", nb_points_non_couverts);
		 else
		 	printf("\nLA LISTE DES POINTS NON COUVERTS EST NULLE\n");

		 for(int h = 0; h < listePolygone[0]->nbPoint; h++){
		 		if(listePolygone[0]->listePointPoly[h]->etat == 'i')
		 			printf("point %d   x:%f y:%f\n", id_point, listePolygone[0]->listePointPoly[h]->x, listePolygone[0]->listePointPoly[h]->y);
		 }
	

		pointp* entete_vus, *entete_visites, *entete_non_vus;

        entete_vus = init_point_liste_points();
        entete_visites = init_point_liste_points();
        entete_non_vus = init_point_liste_points();

        entete_visites->next = visites;
        entete_vus->next = vus;
        entete_non_vus->next = non_vus;

       // afficher_liste_point(entete_visites);
        //afficher_liste_point(entete_vus);
        //afficher_liste_point(entete_non_vus);
		
	//afficher_liste_polygone(listeDepart);

	pointp* l1 = init_sommet();
	draw_probleme(listeDepart, l1);



	/* 
	TEST PERMETTANT D'AFFICHER SEULEMENT LA GRILLE DU POLYGONE ENGLOBANT

	pointp *grille = NULL, *grille_last, *grille_next;int v = 0;
	printf("TEST: DESSIN DE LA GRILLE DU POLYGONE ENGLOBANT\n");
	for(int a = 0; a < listePolygone[0]->nbPoint; a++){		
						printf("point %d   x:%f y:%f\n", listePolygone[0]->listePointPoly[a]->id, listePolygone[0]->listePointPoly[a]->x, listePolygone[0]->listePointPoly[a]->y);
						
						
						// on ajoute le point à la liste chaînée des points visités
						
		
						grille_next = listePolygone[0]->listePointPoly[a];
				

						if(v++ == 0){ 
							grille = grille_next; 
							grille_last = grille;
						}
						else{
							grille_last->next = grille_next;
							grille_last = grille_last->next;
						}
		}
		entete_visites->next = NULL;
		entete_vus->next = NULL;

		draw_resultat(listeDepart, entete_visites, entete_vus, grille);

		*/
		


        draw_resultat(listeDepart, entete_visites, entete_vus, entete_non_vus);
        break;
	}}

	
	



	fclose(fichier);



	return 0;
}
