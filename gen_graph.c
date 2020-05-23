#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gen_point.h"



//float distance;
int ** coveredBy;


#define distanceCouverture 3.250
#define distanceVoisin 1.500

liste_polygone* polygones;

  
double max(double a, double b)
{
    if(a > b)
        return a;
    else
        return b; 
}

double min(double a, double b)
{
    if(a < b)
        return a;
    else
        return b; 
}

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(point* p, point* q, point* r) 
{ 
    if (q->x <= max(p->x, r->x) && q->x >= min(p->x, r->x) && 
        q->y <= max(p->y, r->y) && q->y >= min(p->y, r->y)) 
       return true; 
  
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(point* p, point* q, point* r) 
{ 
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
    // for details of below formula. 
    int val = (q->y - p->y) * (r->x - q->x) - 
              (q->x - p->x) * (r->y - q->y); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(point* p1, point* q1, point* p2, point* q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 

// permet de savoir si le segment formé des points lePolygone->listePointPoly[i] et lePolygone->listePointPoly[j] croise une des arrêtes 
bool intersection(polygone *lePolygone, int i, int j){

	liste_polygone* lesPolygones = polygones;
	point* sommet; 

	// pour chaque polygone 
	while(lesPolygones->next != NULL){
		sommet = lesPolygones->polygone;

		// pour chaque arrête [sommet sommet->next] du polygone
		while(sommet != lesPolygones->polygone){
				if(doIntersect(lePolygone->listePointPoly[i], lePolygone->listePointPoly[j], sommet, sommet->next))
					return true;
			sommet = sommet->next;
		}


		lesPolygones = lesPolygones->next;
	}

	return false;

}



/*
* Génération du graphe
* Listes de l'ensemble des points en paramètre
*/
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
		for(int j = i; j < lePolygone->nbPoint; j++)
		{
			// distance euclidienne entre les 2 pts
			distance = sqrtf((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x)*(lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x) + (lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y)*(lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y));

			accesDirect = !intersection(lePolygone,i,j);

			// les pts sont voisins ?
			if(distance <= distanceVoisin && accesDirect)
			{
				printf("< %d %d >,", lePolygone->listePointPoly[i]->id, lePolygone->listePointPoly[j]->id);
			}

			// les pts se couvrent ?
			if(distance <= distanceCouverture && accesDirect)
			{
				coveredBy[lePolygone->listePointPoly[i]->id] = realloc(coveredBy[lePolygone->listePointPoly[i]->id], (++nb_points_couvrant[lePolygone->listePointPoly[i]->id])*sizeof(int));
				coveredBy[lePolygone->listePointPoly[i]->id][nb_points_couvrant[lePolygone->listePointPoly[i]->id] - 1] = lePolygone->listePointPoly[j]->id;

				coveredBy[lePolygone->listePointPoly[j]->id] = realloc(coveredBy[lePolygone->listePointPoly[j]->id], (++nb_points_couvrant[lePolygone->listePointPoly[j]->id])*sizeof(int));
				coveredBy[lePolygone->listePointPoly[j]->id][nb_points_couvrant[lePolygone->listePointPoly[j]->id] - 1] = lePolygone->listePointPoly[i]->id;
			}
		}
	}

	printf("};\n");

	printf("CoveredBy = [\n");

	for(int k = 0; k < lePolygone->nbPoint; k++)
	{
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
