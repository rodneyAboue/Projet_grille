#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(){
	FILE* fichier = fopen("solutions.res","r");

	if(fichier == NULL){
		perror("fopen");
		exit(-1);
	}
	else{
		int nb_sommets_chemin,nb_points_couverts,id_point;
		double longueur_chemin;

		while(fscanf(fichier, "%d %lf", &nb_sommets_chemin,&longueur_chemin) != EOF){
			printf("CHEMIN :\n%d sommets\nlongueur = %f\n\n", nb_sommets_chemin,longueur_chemin);

			for(int i = 1; i <= nb_sommets_chemin; i++){
				fscanf(fichier,"%d", &id_point);
				printf("sommet %d\n", id_point);
			}

			fscanf(fichier,"%d", &nb_points_couverts);

			printf("\nliste des %d points couverts :\n", nb_points_couverts);

			for(int j = 1; j <= nb_points_couverts; j++){
				fscanf(fichier,"%d ", &id_point);
				printf("point couvert d'id %d\n", id_point);
			}
		}
	}

	fclose(fichier);

	return 0;
}
