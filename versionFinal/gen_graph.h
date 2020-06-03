#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "gen_point.h"

#ifndef GEN_GRAPH_H
#define GEN_GRAPH_H

/*
* bool intersection(polygone*, int, int, liste_polygone*);
* Vérifie si un segment entre 2 points du tableau se coupe une arrete
* Argument:
* Le polygone qui contient la liste des points, les 2 indices du tableau correspondant au point à tester et la liste de polygone
* Return:
* Un boolean qui indique si il y a une intersection (true) ou non
*/
bool intersection(polygone *lePolygone, int i, int j, liste_polygone*);

/*
* genererGrahe(liste_polygone*, polygone*);
* Compare les distances et les intersections entre les points et remplis un fichier avec l'ensemble des voisins et des points couverts
* Argument:
* La liste de polygone pour éviter d'indiquer des points voisins alors qu'il y a un obstacle, et le polygone contenant la liste des points
* Return:
* Rien, le fichier tspp.dat est créé
*/
void genererGraphe(liste_polygone*, polygone*);

#endif
