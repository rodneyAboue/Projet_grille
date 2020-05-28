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
	//Permet de savoir si c'est un polygone standart ou interdit;
	// s -> standart, i -> interdit
	char type;
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
* creerPolyInterdit();
* Créer un polygone dit "interdit" qui va pouvoir stocker les points interdit au besoin;
* Argument:
* Un sommet du polygone
* Return:
* Une structure polygone
*/
polygone* creerPolyInterdit(pointp *);

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
* Le polygone, le point de départ et la distance entre les voisins
* Return: 
* Rien, la liste de point du polygone est modifié, il n'est donc pas nécessaire de renvoyer celui-ci
*/
void gen_point(polygone*, pointp*, float);

/*
*
* Retire les points d'un polygone dit interdit à un autre polygone et les stocks
* Argument:
* Le polygone interdit et le polygone contenant les points
* Return:
* Rien
*/
void delete_point_polygone(polygone*, polygone*);

/*
* delete_point();
* Retire les points d'un polygone dit interdit à un autre polygone mais ne les stocks pas
* Argument:
* Le polygone contenant les points et un sommet du polygone Interdit
* Return:
* Rien
*/
void delete_point_polygone2(polygone* , pointp*);

/*
* verif_Voisin();
* Vérifie que 2 voisins ne sont pas séparé par une arete du polygone
* Argument:
* Le polygone, et les 2 points supposés voisins
* Return:
* Booleen indiquant si oui ou non ils sont voisins
*/
bool verif_Voisin(polygone*, pointp*, pointp*);

bool gen_point_polygone_TEMPORAIRE(polygone*, pointp*, float);
void gen_point_TEMPORAIRE(polygone*, pointp*, bool, bool, bool, bool, bool, float);
