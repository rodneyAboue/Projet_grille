#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gen_point.h"

#ifndef GEN_GRAPH_H
#define GEN_GRAPH_H

void genererGraphe(liste_polygone*, polygone*);
bool intersection(polygone *lePolygone, int i, int j, liste_polygone*);


#endif
