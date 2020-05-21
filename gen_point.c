#include "gen_point.h"

polygone * creerPoly(point * unSommet){
	polygone * lePoly = (polygone*)malloc(1*sizeof(polygone));
	lePoly->nbPoint = 0;
	lePoly->sommetPoly = unSommet;
	lePoly->listePointPoly=(point**)malloc(lePoly->nbPoint*sizeof(point*));
	lePoly->type = 's';
	return lePoly;
}

polygone* creerPolyInterdit(point* unSommet){
	polygone * lePoly = creerPoly(unSommet);
	lePoly->type = 'i';
	return lePoly;
}

// Vérifier que le point se trouve dans le polygone
bool pointIsInPoly(point* lePoint, point* lePolygone){
	bool isInside = false;

	int minX, minY, maxX, maxY;
	minX = lePolygone->x; 
	minY = lePolygone->y;
	maxX = minX; 
	maxY = minY; 

	//Recuperer le maximum et minimum des coordonnées x/y
	point* sommetSuivant = lePolygone->next;
	while(sommetSuivant->id != lePolygone->id){ 
		if(sommetSuivant->x < minX){
			minX = sommetSuivant->x;
		}else if(sommetSuivant->x > maxX){
			maxX = sommetSuivant->x;
		}

		if(sommetSuivant->y < minY){
			minY = sommetSuivant->y;
		}else if(sommetSuivant->y > maxY){
			maxY = sommetSuivant->y;
		}
		sommetSuivant = sommetSuivant->next;
	}

	//Vérifier que le point se trouve bien dans le carré dont les sommets sont le minimum et le maximum de chaque axe
	if(lePoint->x < minX || lePoint->x > maxX || lePoint->y < minY || lePoint->y > maxY){
		return false;
	}

	

	point* sommet_courant = lePolygone
	point* sommet_suivant = lePolygone->next;

	while(sommet_suivant->id != lePolygone->id){
		if((sommet_suivant->y > lePoint->y) != (sommet_courant->y > lePoint->y)
		&&
		lePoint->x < (((sommet_courant->x - sommet_suivant->x)*(lePoint->y - sommet_suivant->y)) / ((sommet_courant->y - sommet_suivant->y) + sommet_suivant->x))){
			isInside = !isInside;
		}

		sommet_courant = sommet_suivant;
		sommet_suivant = sommet_suivant->next;
	}
	return isInside;

}

// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone(polygone* lePolygone, point* pointDepart, float distanceVoisin){
	if(pointIsInPoly(pointDepart, lePolygone) == false){
		return false;
	}
	lePolygone->listePointPoly = (point **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
	lePolygone->listePointPoly[lePolygone->nbPoint - 1] = pointDepart;
	gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
	return true;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point(polygone* lePolygone, point* pointDepart, float distanceVoisin){
	point* nouveauPoint = init_point();
	//Point à gauche
	nouveauPoint->x = pointDepart->x - distanceVoisin;
	nouveauPoint->y = pointDepart->y;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
		}
	}

	//Point à droite
	nouveauPoint->x = pointDepart->x + distanceVoisin;
	nouveauPoint->y = pointDepart->y;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
		}
	}


	//Point en haut
	nouveauPoint->x = pointDepart->x;
	nouveauPoint->y = pointDepart->y + distanceVoisin;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
			nouveauPoint = init_point();
		}
	}

	// Point en bas
	nouveauPoint->x = pointDepart->x;
	nouveauPoint->y = pointDepart->y - distanceVoisin;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
			if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
				existant = true;
			}
		}
		if(!existant){
			lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
		}
	}
}

void delete_point(polygone* lePoly, polygone* lePolyInterdit){
	for(int i = 0; i< lePoly->nbPoint; i++){
		if(pointIsInPoly(lePoly->listePointPoly[i], lePolyInterdit) == true){
			lePolyInterdit->listePointPoly = (point**)realloc(lePolyInterdit->listePointPoly, ++(lePolyInterdit->nbPoint)*sizeof(point*));
			lePolyInterdit->listePointPoly[lePolyInterdit->nbPoint-1] = lePoly->listePointPoly[i];
			for(int j = i; j < lePoly->nbPoint -1; j++){
				lePoly->listePointPoly[j] = lePoly->listePointPoly[j+1];
			}
			lePoly->listePointPoly = (point**)realloc(lePoly->listePointPoly, --(lePoly->nbPoint)*sizeof(point*));
			i--;
		}
	}
}
