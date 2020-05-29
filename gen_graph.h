#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "gen_point.h"

#ifndef GEN_GRAPH_H
#define GEN_GRAPH_H

extern liste_polygone* polygones;

void genererGraphe(polygone *lePolygone);
void genererGraphe_SECOUR(polygone*);
bool intersection(polygone *lePolygone, int i, int j);


#endif
