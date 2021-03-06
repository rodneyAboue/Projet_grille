#include "gen_point.h"

// Define Infinite (Using INT_MAX caused overflow problems)
#define INF 10000

// Création d'un structure polygone à partir d'un sommet
polygone * creerPoly(pointp * unSommet){
	polygone * lePoly = (polygone*)malloc(1*sizeof(polygone));
	lePoly->nbPoint = 0;
	lePoly->sommetPoly = unSommet;
	lePoly->listePointPoly=(pointp**)malloc(lePoly->nbPoint*sizeof(pointp*));
	return lePoly;
}

// Retourne la valeur la plus faible entre la variable a & b
double min(double a, double b){
    	return (a < b) ? a : b;
}

// Retourne la valeur la plus forte entre la variable a & b
double max(double a, double b){
    	return (a > b) ? a : b;
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(pointp* p, pointp* q, pointp* r){
    	if ( q->x <= max(p->x, r->x) && q->x >= min(p->x, r->x) && q->y <= max(p->y, r->y) && q->y >= min(p->y, r->y)){
	        return true;
	}
    	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(pointp* p, pointp* q, pointp* r){
	int val = ((q->y - p->y) * (r->x - q->x)) - ((q->x - p->x) * (r->y - q->y));
    	if (val == 0) return 0; // colinear
    	return (val > 0)? 1: 2; // clock or counterclock wise
}

// The function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(pointp* p1, pointp* q1, pointp* p2, pointp* q2){
    	// Find the four orientations needed for general and
    	// special cases
    	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
    	int o3 = orientation(p2, q2, p1);
    	int o4 = orientation(p2, q2, q1);

    	// General case
    	if (o1 != o2 && o3 != o4){
        	return true;
	}

	// Special Cases
    	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
    	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
    	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
   	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
    	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

// Returns true if lePoint lies inside lePolygone with n vertices
bool isInside(pointp * lePoint, polygone* lePolygone){
    	// Create a point for line segment from lePoint to infinite
    	pointp* extreme = init_sommet();
    	extreme->x = INF;
    	extreme->y = lePoint->y;
    	pointp* sommet = lePolygone->sommetPoly;
    	// Count intersections of the above line with sides of polygon
	int count = 0;
	do{
  		// Check if the line segment from 'lePoint' to 'extreme' intersects
        	// with the line segment from 'sommet' to 'sommet->next'
        	if (doIntersect(sommet, sommet->next, lePoint, extreme)){
            		// If 'lePoint' is colinear with line segment 'sommet-sommet->next',
            		// then check if it lies on segment. If it lies, return true,
            		// otherwise false
            		if (orientation(sommet, lePoint, sommet->next) == 0){
               			return onSegment(sommet, lePoint, sommet->next);
			}
            		count++;
        	}
        	sommet = sommet->next;
    	} while (sommet->id != lePolygone->sommetPoly->id);
    	// Return true if count is odd, false otherwise
    	return count&1;  // Same as (count%2 == 1)
}


// Vérifie le point de départ et lance ensuite la création des points
bool gen_point_polygone(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	if(!isInside(pointDepart, lePolygone)){
		return false;
	}
	lePolygone->listePointPoly = (pointp **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
	pointp* nouveauPoint = init_point_liste_points(); // pour avoir un id de point correct (compris entre 0 et le nb de pts de la grille-1)
	nouveauPoint->x = pointDepart->x;
	nouveauPoint->y = pointDepart->y;
	lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
	gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
	return true;
}

// Générer l'ensemble des points de manière récursive
void gen_point(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	pointp* nouveauPoint = init_point_liste_points();
	//Point à l'OUEST
	// Ajustement des coordonnées avec la distance de création
	nouveauPoint->x = pointDepart->x - distanceVoisin;
	nouveauPoint->y = pointDepart->y;
	//On vérifie que le nouveau point se trouve bien dans le polygone
	if(isInside(nouveauPoint, lePolygone) == true){
		// On vérifie si le point n'existe pas
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		// Si il n'existe pas
		if(!existant){
			// On aggrandie l'allocation en mémoire du tableau de point
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			// On appel de nouveau la fonction avec le point fraîchement ajouté à la liste
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point_liste_points();
		}
	}

	//Point à l'EST
	nouveauPoint->x = pointDepart->x + distanceVoisin;
	nouveauPoint->y = pointDepart->y;
	if(isInside(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point_liste_points();
		}
	}


	//Point au NORD
	nouveauPoint->x = pointDepart->x;
	nouveauPoint->y = pointDepart->y + distanceVoisin;
	if(isInside(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point_liste_points();
		}
	}

	// Point au SUD
	nouveauPoint->x = pointDepart->x;
	nouveauPoint->y = pointDepart->y - distanceVoisin;
	if(isInside(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point_liste_points();
		}
	}else{
		free(nouveauPoint);
	}
}

// Retire l'ensemble des points du polygone qui se trouvent dans le polygone interdit
void delete_point_polygone(polygone* lePoly, polygone* lePolyInterdit){
	for(int i = 0; i< lePoly->nbPoint; i++){
		if(isInside(lePoly->listePointPoly[i], lePolyInterdit) == true){
			free(lePoly->listePointPoly[i]);
			lePoly->listePointPoly[i] = lePoly->listePointPoly[lePoly->nbPoint-1];
			lePoly->listePointPoly = (pointp**)realloc(lePoly->listePointPoly, --(lePoly->nbPoint)*sizeof(pointp*));
			i--;
		}
	}
}
