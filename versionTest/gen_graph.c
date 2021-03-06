#include "gen_graph.h"

//float distance;
int ** coveredBy;

#define distanceCouverture 0.025
#define distanceVoisin 0.01

// permet de savoir si le segment formé des points lePolygone->listePointPoly[i] et lePolygone->listePointPoly[j] croise une des arrêtes 
bool intersection(polygone *lePolygone, int i, int j, liste_polygone* polygones){

	liste_polygone* lesPolygones = polygones;
	pointp* sommet; 

	// pour chaque polygone 
	while(lesPolygones->next != NULL){
		lesPolygones = lesPolygones->next;
		sommet = lesPolygones->polygone;

		// pour chaque arrête [sommet sommet->next] du polygone
		while(sommet != lesPolygones->polygone){
			if(doIntersect(lePolygone->listePointPoly[i], lePolygone->listePointPoly[j], sommet, sommet->next)){
				return true;
			}
			sommet = sommet->next;
		}

	}

	return false;

}

/*
* Génération du graphe
* Listes de l'ensemble des points en paramètre
*/
/*
void genererGraphe(polygone *lePolygone){
	coveredBy = (int **)malloc(lePolygone->nbPoint * sizeof(int*));
	int nb_points_couvrant[lePolygone->nbPoint]; // tailles des différents tableaux contenus dans coveredBy
	bool accesDirect;
	float distance;
	// Mise à 0 de la couverture
	for(int i = 0; i < lePolygone->nbPoint; i++){
		nb_points_couvrant[i] = 0;
	}
	printf("Edges = {\n");
	for(int i = 0; i < lePolygone->nbPoint; i++)
	{
		for(int j = i+1; j < lePolygone->nbPoint; j++)
		{
			// distance euclidienne entre les 2 pts
			distance = sqrtf((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x)*(lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x) + (lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y)*(lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y));

			accesDirect = !intersection(lePolygone,i,j);
			// les pts sont voisins ?
			if(distance <= distanceVoisin && accesDirect){
				printf("< %d %d >,\n", lePolygone->listePointPoly[i]->id, lePolygone->listePointPoly[j]->id);
			}else{
				// les pts se couvrent ?
				if(distance <= distanceCouverture && accesDirect){
				//	coveredBy[lePolygone->listePointPoly[i]->id] = realloc(coveredBy[lePolygone->listePointPoly[i]->id], (++nb_points_couvrant[lePolygone->listePointPoly[i]->id])*sizeof(int));
				//	coveredBy[lePolygone->listePointPoly[i]->id][nb_points_couvrant[lePolygone->listePointPoly[i]->id] - 1] = lePolygone->listePointPoly[j]->id;

				//	coveredBy[lePolygone->listePointPoly[j]->id] = realloc(coveredBy[lePolygone->listePointPoly[j]->id], ++(nb_points_couvrant[lePolygone->listePointPoly[j]->id])*sizeof(int));
				//	coveredBy[lePolygone->listePointPoly[j]->id][nb_points_couvrant[lePolygone->listePointPoly[j]->id] - 1] = lePolygone->listePointPoly[i]->id;
				}
			}
		}
	}
	printf("};\n");
	printf("CoveredBy = [\n");
	for(int k = 0; k < lePolygone->nbPoint; k++){
		printf("{ ");
		for(int m = 0; m < nb_points_couvrant[lePolygone->listePointPoly[k]->id]; m++)
		{
			if(m != nb_points_couvrant[lePolygone->listePointPoly[k]->id] - 1)
				printf("%d, ", coveredBy[lePolygone->listePointPoly[k]->id][m]);
			else
				printf("%d ", coveredBy[lePolygone->listePointPoly[k]->id][m]);	
		}
		printf("},\n");
	}
	printf("];\n");
}
*/
void genererGraphe(liste_polygone* lesPolygones, polygone* lePolygone){
	bool accesDirect;
	float distance;

	FILE * fichier = fopen("tspp.dat", "w");
	fprintf(fichier ,"Edges: {\n");
	for(int i = 0; i < lePolygone->nbPoint; i++){
		for(int j = i + 1; j < lePolygone->nbPoint; j++){
			distance = sqrtf(pow((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x),2) + pow((lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y),2));
			accesDirect = !intersection(lePolygone, i, j, lesPolygones);
			if(distance <= distanceVoisin /*&& accesDirect*/){
				fprintf(fichier, "< %d %d >,\n", lePolygone->listePointPoly[i]->id, lePolygone->listePointPoly[j]->id);
			}
		}
	}
	fseek(fichier, -2, SEEK_END); // écrase la dernière virgule
	fprintf(fichier, "\n};\n");

	fprintf(fichier, "CoveredBy = [\n");
	for(int i = 0; i < lePolygone->nbPoint; i++){
		for(int j = i+1; j< lePolygone->nbPoint; j++){
			distance = sqrtf(pow((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x),2) + pow((lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y),2));
			accesDirect = !intersection(lePolygone, i, j, lesPolygones);
			if(distance <= distanceCouverture /*&& accesDirect*/){
				fprintf(fichier, "< %d %d >,\n", lePolygone->listePointPoly[i]->id, lePolygone->listePointPoly[j]->id);
			}
		}
	}
	fseek(fichier, -2, SEEK_END); // écrase la dernière virgule
	fprintf(fichier, "\n];\n");
	fclose(fichier);
}
