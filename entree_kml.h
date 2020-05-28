#ifndef ENTREE_KML
#define ENTREE_KML

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "structure_point_polygone.h"


//avance le curseur à la balise <coordinates> suivant
// = le debut des coordonnées d'un polygone
//retourne 1 si il y en a une
// 0 sinon
int next_polygone(FILE* f);

//prend en parametre un FILE* d'un export kml
//retourne le polygone présen à la suite du curseur de parcours du ficher
pointp* create_polygone(FILE* f);

//prend en entrée un export.kml de data.shom et une liste de polygone vide mais initialisée
//extraire polygone remplit la liste de polygone avec ceux detectes dans le .kml
//et retourne un pointeur vers le point de depart si il a ete detecte, NULL sinon 
pointp* extraire_polygones(const char* export, liste_polygone* liste);

#endif
