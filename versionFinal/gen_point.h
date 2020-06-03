#include "structure_point_polygone.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct{
	//Un sommet du polygone
	pointp * sommetPoly;
	//Liste de pointeur de point se trouvant à l'interieur du polygone
	pointp ** listePointPoly;
	//Nombre de point dans le poly hors sommet (nécessaire pour parcourir la liste)
	int nbPoint;
}polygone;



/*
* creerPoly();
* Créer la structure polygone à partir d'un sommet;
* Argument:
* Un sommet du polygone
* Return:
* Une structure polygone
*/
polygone* creerPoly(pointp *);


/*
* isInside() + fonctions que utilise isInside();
* Vérifie si un point se trouve dans le polygone
* Argument:
* Le point à vérifier et le polygone
* Return:
* Un booleen qui indique vrai si le point se trouve dans le polygone, faux sinon
*/
double min(double a, double b);
double max(double a, double b);
bool onSegment(pointp* p, pointp* q, pointp* r);
int orientation(pointp* p, pointp* q, pointp* r) ;
bool doIntersect(pointp* p1, pointp* q1, pointp* p2, pointp* q2) ;
bool isInside(pointp * lePoint, polygone* lePolygone) ;

/*
* gen_point_polygone();
* Vérifie si le point de départ se trouve bien dans le polygone, puis démarre la création de point
* Argument:
* Le polygone, le point de départ et la distance entre les voisins
* Return:
* Un booleen qui indique si la création a été effectuée.
*/
bool gen_point_polygone(polygone*, pointp*, float);

/*
* gen_point();
* Génère les points de facon récursive;
* Argument:
* Le polygone, le point de départ et la distance entre les points
* Return: 
* Rien, la liste de point du polygone est modifié, il n'est donc pas nécessaire de renvoyer celui-ci
*/
void gen_point(polygone*, pointp*, float);

/*
*
* Vérifie et retire l'ensemble des points d'un polygone aillant des coordonnées se trouvant dans un
* polygone interdit
* Argument:
* Le polygone interdit et le polygone contenant les points
* Return:
* Rien
*/
void delete_point_polygone(polygone*, polygone*);

