#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structure_1.h"


int nb_point;
float distance;
int * coveredBy;
int nb_points_couvrant[nb_points]; // tailles des différents tableaux contenus dans coveredBy

/*
* Génération du graphe
* Listes de l'ensemble des points en paramètre
*/
void genererGraphe(liste_point points, float distanceVoisin, float distanceCouverture){
	nb_points = points.nb_point;
	coveredBy = (int *)malloc(nb_points * sizeof(int))
	
	// Mise à 0 de la couverture
	for(int i = 0; i < nb_points; i++){
		nb_points_couvrant[i] = 0;
	}
	
	for(int i = 0; i < nb_points; i++)
	{
		for(int j = i; j < nb_points; j++)
		{
			// distance euclidienne entre les 2 pts
			distance = sqrtf((points.liste[i].x - points.liste[j].x)*(points.liste[i].x - points.liste[j].x) + (points.liste[i].y - points.liste[j].y)*(points.liste[i].y - points.liste[j].y));

			// les pts sont voisins ?
			if(distance <= distanceVoisin)
			{
				points[i].voisins.liste = (point *) realloc(points[i].voisins.liste, ++(points[i].voisins.nb_point)*sizeof(point));
				points[i].voisins.liste[points[i].voisins.nb_point - 1] = points.liste[j];

				points[j].voisins.liste = (point *) realloc(points[j].voisins.liste, ++(points[j].voisins.nb_point)*sizeof(point));
				points[j].voisins.liste[points[j].voisins.nb_point - 1] = points.liste[i];
			}

			// les pts se couvrent ?
			if(distance <= distanceCouverture)
			{
				coveredBy[i] = realloc(coveredBy[i], (++nb_points_couvrant[i])*sizeof(int));
				coveredBy[i][nb_points_couvrant[i] - 1] = points.liste[j].id;

				coveredBy[j] = realloc(coveredBy[j], (++nb_points_couvrant[j])*sizeof(int));
				coveredBy[j][nb_points_couvrant[j] - 1] = points.liste[i].id; 
			}
		}
	}
}

/*
* Affichage du graphe
* Model pour la mise en fichier
*/
void afficherGraphe(){
	// permet de sauvegarder les arrêtes qui ont été affichées, pour éviter d'afficher < x y > si on a déjà affiché < y x >
	int edges[nb_points][nb_points]; // 0 = l'arrête n'a encore pas été affichée, 1 = l'arrête a déjà été affichée

	int min, max;

	for(int i = 0; i < nb_points; i++)
		for(int j = 0; i < nb_points; j++)
			edges[i][j] = 0;

	printf("Edges = {\n");

	for(int k = 0; k < nb_point; k++)
	{
		for(int m = 0; m < points.liste[k].voisins.nb_point; m++)
		{
			if(edges[points.liste[k].id][points.liste[m].id] == 0 && edges[points.liste[m].id][points.liste[k].id] == 0)
			{
				min = (points.liste[k].id < points.liste[m].id) ? points.liste[k].id : points.liste[m].id;

				max = (points.liste[k].id > points.liste[m].id) ? points.liste[k].id : points.liste[m].id;

				edges[min][max] = 1;

				printf("< %d %d >,", min, max);
			}
		}
	}

	printf("};\n");

	printf("CoveredBy = [\n");
	for(int k = 0; k < nb_point; k++)
	{
		printf("{ ");
		for(int m = 0; m < points.liste[k].voisins.nb_point; m++)
		{
			if(m != points.liste[k].voisins.nb_point)
				printf("%d, ", points.liste[k].voisins.liste[m].id);
			else
				printf("%d ", points.liste[k].voisins.liste[m].id);		
		}
		printf("},\n");
	}
	printf("];\n");
}