#include "structure_point_polygone.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct{
	//Un sommet du polygone
	point * sommetPoly;
	//Liste de pointeur de point se trouvant à l'interieur du polygone
	point ** listePointPoly;
	//Nombre de point dans le poly hors sommet (nécessaire pour parcourir la liste)
	int nbPoint;
}polygone;

/*
* creerPoly();
* Créér la structure polygone à partir d'un sommet;
* Argument:
* Un sommet du polygone
* Return:
* Une structure polygone
*/
polygone* creerPoly(point *);

/*
* pointIsInPoly();
* Vérifie si un point via ces coordonnées se trouve dans le polygone
* Argument:
* Le point à vérifier et le polygone
* Return:
* Un booleen qui indique vrai si le point se trouve dans le polygone, faux sinon
*/
bool pointIsInPoly(point*, polygone*);

/*
* gen_point_polygone();
* Vérifie si le point de départ se trouve bien dans le polygone, puis démarre la création de point
* Argument:
* Le polygone, le point de départ et la distance entre les voisins
* Return:
* Un booleen qui indique si la création a été effectuée.
*/
bool gen_point_polygone(polygone*, point*, float);

/*
* gen_point();
* Génère les points de facon récursive;
* Argument:
* Le polygone, le point de départ et la distance entre les voisins
* Return: 
* Rien, la liste de point du polygone est modifié, il n'est donc pas nécessaire de renvoyer celui-ci
*/
void gen_point(polygone*, point*, float);
