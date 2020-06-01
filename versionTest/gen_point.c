#include "gen_point.h"
#include <stdbool.h>
//#include <unistd.h>

// Define Infinite (Using INT_MAX caused overflow problems) 
#define INF 10000 

polygone * creerPoly(pointp * unSommet){
	polygone * lePoly = (polygone*)malloc(1*sizeof(polygone));
	lePoly->nbPoint = 0;
	lePoly->sommetPoly = unSommet;
	lePoly->listePointPoly=(pointp**)malloc(lePoly->nbPoint*sizeof(pointp*));
	return lePoly;
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}

double max(double a, double b)
{
    return (a > b) ? a : b;
}
  
// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(pointp* p, pointp* q, pointp* r) 
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
int orientation(pointp* p, pointp* q, pointp* r) 
{ 
    int val = (q->y - p->y) * (r->x - q->x) - 
              (q->x - p->x) * (r->y - q->y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(pointp* p1, pointp* q1, pointp* p2, pointp* q2) 
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
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(pointp * lePoint, polygone* lePolygone) 
{ 
      
    // Create a point for line segment from p to infinite 
    pointp* extreme = init_point();
    
    extreme->x = INF;
    extreme->y = lePoint->y;
  
    pointp* sommet = lePolygone->sommetPoly;

    // Count intersections of the above line with sides of polygon 
    int count = 0; 
    do
    {     

  	// Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(sommet, sommet->next, lePoint, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(sommet, lePoint, sommet->next) == 0) 
               return onSegment(sommet, lePoint, sommet->next); 
  
            count++; 
        } 
        sommet = sommet->next; 
    } while (sommet->id != lePolygone->sommetPoly->id); 

	

    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 

// Vérifier le point de départ et lancer ensuite la création des points
/*bool gen_point_polygone_TEMPORAIRE(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	if(isInside(pointDepart, lePolygone) == false){
		return false;
	}
	lePolygone->listePointPoly = (pointp **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
	lePolygone->listePointPoly[0] = pointDepart;
	gen_point_TEMPORAIRE(lePolygone, pointDepart,false,true,true,true,true, distanceVoisin);
	return true;
}*/

// Générer l'ensemble des points à partir d'un point de départ
/*void gen_point_TEMPORAIRE(polygone* lePolygone, pointp* pointDepart, bool point_sur_arrete,bool explorer_nord, bool explorer_sud, bool explorer_ouest, bool explorer_est, float distanceVoisin){
	pointp* nouveauPoint = init_point();
	pointp* nouveauPoint2 = init_point();

	bool nord;
	bool sud;
	bool ouest;
	bool est;
	bool cote_proche = false;
	int i;
	bool pointOutsidePoly;
	int diviseur;
	bool existant;

	if(explorer_ouest){

		nouveauPoint->x = pointDepart->x - distanceVoisin;
		nouveauPoint->y = pointDepart->y;


		if(pointIsInPoly(nouveauPoint, lePolygone) == false && !point_sur_arrete){
			i = 0;
			pointOutsidePoly = false;
			diviseur = 2;


			// recherche dichotomique du point qui est situé sur l'arrête
			while(i < 5 || i >= 5 && !pointIsInPoly(nouveauPoint, lePolygone)){
				if(pointOutsidePoly)
					nouveauPoint->x = pointDepart->x + distanceVoisin/diviseur;
				else
					nouveauPoint->x = pointDepart->x - distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y  + distanceVoisin;

			nord = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y - distanceVoisin;

			sud = pointIsInPoly(nouveauPoint2, lePolygone);

			cote_proche = true;
		}
		
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			
			if(!existant){
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,nord&&cote_proche || !cote_proche,sud&&cote_proche || !cote_proche,!cote_proche,false, distanceVoisin);
				nouveauPoint = init_point();
			}
		}
	}
	if(explorer_est){

		nouveauPoint->x = pointDepart->x + distanceVoisin;
		nouveauPoint->y = pointDepart->y;


		if(pointIsInPoly(nouveauPoint, lePolygone) == false && !point_sur_arrete){
			i = 0;
			pointOutsidePoly = false;
			diviseur = 2;


			// recherche dichotomique du point qui est situé sur l'arrête
			while(i < 5 || i >= 5 && !pointIsInPoly(nouveauPoint, lePolygone)){
				if(pointOutsidePoly)
					nouveauPoint->x = pointDepart->x - distanceVoisin/diviseur;
				else
					nouveauPoint->x = pointDepart->x + distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}
			cote_proche = true;

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y  + distanceVoisin;

			nord = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y - distanceVoisin;

			sud = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,nord&&cote_proche || !cote_proche,sud&&cote_proche || !cote_proche,false,!cote_proche, distanceVoisin);
				nouveauPoint = init_point();
			}
		
	}
	if(explorer_nord){

		nouveauPoint->x = pointDepart->x;
		nouveauPoint->y = pointDepart->y + distanceVoisin;
		if(pointIsInPoly(nouveauPoint, lePolygone) == false && !point_sur_arrete){
			i = 0;
			pointOutsidePoly = false;
			diviseur = 2;
			// recherche dichotomique du point qui est situé sur l'arrête
			while(i < 5 || i >= 5 && !pointIsInPoly(nouveauPoint, lePolygone)){
				if(pointOutsidePoly)
					nouveauPoint->y = pointDepart->y - distanceVoisin/diviseur;
				else
					nouveauPoint->y = pointDepart->y + distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}
			cote_proche = true;
			nouveauPoint2->x = pointDepart->x - distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			ouest = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x + distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			est = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,!cote_proche,false,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche, distanceVoisin);
				nouveauPoint = init_point();
			}
		
	}
	if(explorer_sud){

		nouveauPoint->x = pointDepart->x;
		nouveauPoint->y = pointDepart->y - distanceVoisin;


		if(pointIsInPoly(nouveauPoint, lePolygone) == false && !point_sur_arrete){
			i = 0;
			pointOutsidePoly = false;
			diviseur = 2;


			// recherche dichotomique du point qui est situé sur l'arrête
			while(i < 5 || i >= 5 && !pointIsInPoly(nouveauPoint, lePolygone)){
				if(pointOutsidePoly)
					nouveauPoint->y = pointDepart->y + distanceVoisin/diviseur;
				else
					nouveauPoint->y = pointDepart->y - distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}
			cote_proche = true;

			nouveauPoint2->x = pointDepart->x - distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			ouest = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x + distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			est = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,false,!cote_proche,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche, distanceVoisin);
				nouveauPoint = init_point();
			}
		
	}

}




*/

// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	if(!isInside(pointDepart, lePolygone)){
		return false;
	}
	lePolygone->listePointPoly = (pointp **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
	lePolygone->listePointPoly[lePolygone->nbPoint - 1] = pointDepart;
	gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
	return true;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	pointp* nouveauPoint = init_point();

	//Point à l'OUEST
	nouveauPoint->x = pointDepart->x - distanceVoisin;
	nouveauPoint->y = pointDepart->y;
	if(isInside(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			//printf("x: %f   y: %f\n", nouveauPoint->x,nouveauPoint->y);
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
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
			//printf("x: %f   y: %f\n", nouveauPoint->x,nouveauPoint->y);
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
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
			//printf("x: %f   y: %f\n", nouveauPoint->x,nouveauPoint->y);
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
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
			//printf("x: %f   y: %f\n", nouveauPoint->x,nouveauPoint->y);
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
		}
	}
}

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

bool verif_Voisin(polygone* lePoly, pointp* depart, pointp* destination){
	pointp * sommet1 = lePoly->sommetPoly;
	pointp * sommet2 = sommet1->next;
	//Nécessaire pour boucle
	int x = sommet2->x;
	int y = sommet2->y;
	for(int w = 0; (w < 1 || sommet2->x != x || sommet2->y !=y); w++){
		float a1 = 0; float a2 = 0;
		float b1,b2;
		if((depart->x - destination->x) != 0 && (sommet1->x - sommet2->x)!=0){
			a1 = (depart->y - destination->y)/ (depart->x - destination->x);
			b1 = (depart->y - (a1*depart->x));
			a2 = (sommet1->y - sommet2->y)/(sommet1->x - sommet2->x);
			b2 = (sommet1->y - (a2*sommet1->x));
		}
		if((a1 - a2) != 0){
			float m = (b2 - b1)/(a1 - a2);
			//printf("Valeur m : %f\n", m);
			if(depart->x < destination->x){
				if(sommet1->x < sommet2->x){
					if(depart->x < m && destination->x > m){
						if(sommet1->x < m && sommet2->x > m){
							return false;
						}
					}

				}else{
					if(depart->x < m && destination->x > m){
						if(sommet1->x > m && sommet2->x < m){
							return false;
						}
					}
				}
			}else {
				if(sommet1->x < sommet2->x){
					if(depart->x > m && destination->x < m){
						if(sommet1->x < m && sommet2->x > m){
							return false;
						}
					}

				}else{
					if(depart->x > m && destination->x < m){
						if(sommet1->x > m && sommet2->x < m){
							return false; 
						}
					}
				}
			}
		}
		sommet1 = sommet1->next;
		sommet2 = sommet2->next;
	}
	return true;
}
