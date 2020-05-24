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
polygone* creerPoly(point *);

/*
* creerPolyInterdit();
* Créer un polygone dit "interdit" qui va pouvoir stocker les points interdit au besoin;
* Argument:
* Un sommet du polygone
* Return:
* Une structure polygone
*/
polygone* creerPolyInterdit(point *);

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
bool gen_point_polygone(polygone*, point*, float, char, float);

/*
* gen_point();
* Génère les points de facon récursive;
* Argument:
* Le polygone, le point de départ et la distance entre les voisins
* Return: 
* Rien, la liste de point du polygone est modifié, il n'est donc pas nécessaire de renvoyer celui-ci
*/
void gen_point(polygone*, point*, float, char, float);

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
void delete_point_polygone2(polygone* , point*);

/*
* verif_Voisin();
* Vérifie que 2 voisins ne sont pas séparé par une arete du polygone
* Argument:
* Le polygone, et les 2 points supposés voisins
* Return:
* Booleen indiquant si oui ou non ils sont voisins
*/
bool verif_Voisin(polygone*, point*, point*);

bool gen_point_polygone_TEMPORAIRE(polygone*, point*, float);
void gen_point_TEMPORAIRE(polygone*, point*, bool, bool, bool, bool, bool, float);
