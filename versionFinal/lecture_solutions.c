#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "entree_kml.h"
#include "dislin.h"

int main(){
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
				visites_next = listePolygone[0]->listePointPoly[k];
				visites_next->next = NULL;
											
								
				listePolygone[0]->listePointPoly[k]->etat = 'x';
			}

			fscanf(fichier,"%d", &nb_points_couverts);

			printf("\nliste des %d points couverts :\n", nb_points_couverts);

			for(int j = 1; j <= nb_points_couverts; j++){
				fscanf(fichier,"%d ", &id_point);
				printf("point couvert d'id %d\n", id_point);


				for(int k = 0; k < listePolygone[0]->nbPoint; k++){
					if(listePolygone[0]->listePointPoly[k]->id == id_point && strcmp(listePolygone[0]->listePointPoly[k]->etat,'o') && strcmp(listePolygone[0]->listePointPoly[k]->etat,'x')){ // 'o' = "vu"    'x' = "visité"
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
					if(listePolygone[0]->listePointPoly[l]->id == id_point && strcmp(listePolygone[0]->listePointPoly[l]->etat,'o') && strcmp(listePolygone[0]->listePointPoly[l]->etat,'.') && strcmp(listePolygone[0]->listePointPoly[k]->etat,'x')){ // '.' = "non vu"      'o' = "vu"      'x' = "visité"
						non_vus_next = non_vus;				
						while(non_vus_next != NULL){
							
							non_vus_next = non_vus_next->next;					
						}
						non_vus_next = listePolygone[0]->listePointPoly[l];
						non_vus_next->next = NULL;
											
								
						listePolygone[0]->listePointPoly[l]->etat = '.';					
					}
										
				}


			break; 
		}
	}

	
	



	fclose(fichier);

	return 0;
}
