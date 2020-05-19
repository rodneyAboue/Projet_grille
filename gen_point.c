#include "gen_point.h"

liste_point listePointPolygone;
int nbPoint;

// Vérifier que le point se trouve dans le polygone
bool pointIsInPoly(point lePoint, polygone lePolygone){
	bool isInside = false;
	int minX, minY, maxX, maxY;
	minX = lePolygone.sommets.liste[0]->x;
	minY = lePolygone.sommets.liste[0]->y;
	maxX = minX;
	maxY = minY;
	//Recuperer le maximum et minimum des coordonnées x/y
	for(int i = 1; i < lePolygone.sommets.nb_point; i++){
		if(lePolygone.sommets.liste[i]->x < minX){
			minX = lePolygone.sommets.liste[i]->x;
		}else if(lePolygone.sommets.liste[i]->x > maxX){
			maxX = lePolygone.sommets.liste[i]->x;
		}

		if(lePolygone.sommets.liste[i]->y < minY){
			minY = lePolygone.sommets.liste[i]->y;
		}else if(lePolygone.sommets.liste[i]->y > maxY){
			maxY =lePolygone.sommets.liste[i]->y;
		}
	}
	//Vérifier que le point se trouve bien dans le carré dont les sommets sont le minimum et le maximum de chaque axe
	if(lePoint.x < minX || lePoint.x > maxX || lePoint.y < minY || lePoint.y > maxY){
		return false;
	}

	//Vérifier que le point se trouve dans le polygone en faisant le tour de celui-ci
	int j = lePolygone.sommets.nb_point - 1;
	for(int i = 0; i < lePolygone.sommets.nb_point; j = i++){
		if((lePolygone.sommets.liste[i]->y > lePoint.y) != (lePolygone.sommets.liste[j]->y > lePoint.y)
		&&
		lePoint.x < (((lePolygone.sommets.liste[j]->x - lePolygone.sommets.liste[i]->x)*(lePoint.y - lePolygone.sommets.liste[i]->y)) / ((lePolygone.sommets.liste[j]->y - lePolygone.sommets.liste[i]->y) + lePolygone.sommets.liste[i]->x))){
			isInside = !isInside;
		}
	}
	return isInside;

}

// Vérifier le point de départ et lancer ensuite la création des points
liste_point gen_point_polygone(polygone lePolygone, point pointDepart, float distanceVoisin){
	if(pointIsInPoly(pointDepart, lePolygone) == false){
		return listePointPolygone;
	}
	listePointPolygone.nb_point = lePolygone.sommets.nb_point;
	listePointPolygone.liste = (point **)malloc(sizeof(point*)*listePointPolygone.nb_point);
	for(int i = 0; i < listePointPolygone.nb_point; i++){
		listePointPolygone.liste[i]->x = lePolygone.sommets.liste[i]->x;
		listePointPolygone.liste[i]->y = lePolygone.sommets.liste[i]->y;
		listePointPolygone.liste[i]->etat = lePolygone.sommets.liste[i]->etat;
	}
	gen_point(lePolygone, pointDepart, distanceVoisin);
	return listePointPolygone;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point(polygone lePolygone, point pointDepart, float distanceVoisin){
	point nouveauPoint;
	//Point à gauche
	nouveauPoint.x = pointDepart.x - distanceVoisin;
	nouveauPoint.y = pointDepart.y;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < listePointPolygone.nb_point && existant == false; i++){
			if(nouveauPoint.x == listePointPolygone.liste[i]->x && nouveauPoint.y == listePointPolygone.liste[i]->y){
				existant = true;
			}
		}
		if(!existant){
			listePointPolygone.liste = (point **)realloc(listePointPolygone.liste, ++(listePointPolygone.nb_point)*sizeof(point*));
			listePointPolygone.liste[listePointPolygone.nb_point-1]->x = nouveauPoint.x;
			listePointPolygone.liste[listePointPolygone.nb_point-1]->y = nouveauPoint.y;
			gen_point(lePolygone, nouveauPoint, distanceVoisin);
		}
	}
	//Point à droite
	nouveauPoint.x = pointDepart.x + distanceVoisin;
        nouveauPoint.y = pointDepart.y;
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < listePointPolygone.nb_point && existant == false; i++){
			if(nouveauPoint.x == listePointPolygone.liste[i]->x && nouveauPoint.y == listePointPolygone.liste[i]->y){
				existant = true;
			}
		}
		if(!existant){
			listePointPolygone.liste = (point **)realloc(listePointPolygone.liste, ++(listePointPolygone.nb_point)*sizeof(point));
			listePointPolygone.liste[listePointPolygone.nb_point-1]->x = nouveauPoint.x;
			listePointPolygone.liste[listePointPolygone.nb_point-1]->y = nouveauPoint.y;
			gen_point(lePolygone, nouveauPoint, distanceVoisin);
		}
	}

	//Point en haut
	nouveauPoint.x = pointDepart.x;
        nouveauPoint.y = pointDepart.y - distanceVoisin;
        if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < listePointPolygone.nb_point && existant == false; i++){
			if(nouveauPoint.x == listePointPolygone.liste[i]->x && nouveauPoint.y == listePointPolygone.liste[i]->y){
				existant = true;
			}
		}
		if(!existant){
			listePointPolygone.liste = (point **)realloc(listePointPolygone.liste, ++(listePointPolygone.nb_point)*sizeof(point));
			listePointPolygone.liste[listePointPolygone.nb_point-1]->x = nouveauPoint.x;
			listePointPolygone.liste[listePointPolygone.nb_point-1]->y = nouveauPoint.y;
			gen_point(lePolygone, nouveauPoint, distanceVoisin);
		}
	}
	//Point en bas
	nouveauPoint.x = pointDepart.x;
        nouveauPoint.y = pointDepart.y + distanceVoisin;
        if(pointIsInPoly(nouveauPoint, lePolygone) == true){
		bool existant = false;
		for(int i = 0; i < listePointPolygone.nb_point && existant == false; i++){
			if(nouveauPoint.x == listePointPolygone.liste[i]->x && nouveauPoint.y == listePointPolygone.liste[i]->y){
				existant = true;
			}
		}
		if(!existant){
			listePointPolygone.liste = (point **)realloc(listePointPolygone.liste, ++(listePointPolygone.nb_point)*sizeof(point));
			listePointPolygone.liste[listePointPolygone.nb_point-1]->x = nouveauPoint.x;
			listePointPolygone.liste[listePointPolygone.nb_point-1]->y = nouveauPoint.y;
			gen_point(lePolygone, nouveauPoint, distanceVoisin);
		}
	}

}
