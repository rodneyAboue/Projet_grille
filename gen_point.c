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
bool pointIsInPoly(point* lePoint, polygone* lePolygone){
	bool isInside = false;

	int minX, minY, maxX, maxY;
	minX = lePolygone->sommetPoly->x;
	minY = lePolygone->sommetPoly->y;
	maxX = minX;
	maxY = minY;

	//Recuperer le maximum et minimum des coordonnées x/y
	point* sommetSuivant = lePolygone->sommetPoly->next;
	while(sommetSuivant->x != lePolygone->sommetPoly->x && sommetSuivant->x != lePolygone->sommetPoly->y){
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

	//Vérifier que le point se trouve dans le polygone en faisant le tour de celui-ci
	point * sommet1 = lePolygone->sommetPoly;
	point * sommet2 = sommet1->next;
	int x = sommet1->x;
	int y = sommet1->y;
	for(int i = 0; i < 1 && sommet1->x != x && sommet1->y != y; i++){
		if((sommet2->y > lePoint->y != (sommet1->y > lePoint->y) && lePoint->x < (((sommet1->x - sommet2->x)*(lePoint->y - sommet2->y))/(sommet1->y - sommet2->y) + sommet2->x))){
			isInside = !isInside;
		}
	}
	return isInside;

}



// variable globale distanceVoisin

// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone_TEMPORAIRE(polygone* lePolygone, point* pointDepart){
	if(pointIsInPoly(pointDepart, lePolygone) == false){
		return false;
	}
	lePolygone->listePointPoly = (point **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
	lePolygone->listePointPoly[0] = pointDepart;
	gen_point(lePolygone, pointDepart,false,true,true,true,true);
	return true;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point_TEMPORAIRE(polygone* lePolygone, point* pointDepart, bool point_sur_arrete,bool explorer_nord, bool explorer_sud, bool explorer_ouest, bool explorer_est  ){ 
	point* nouveauPoint = init_point();
	point* nouveauPoint2 = init_point();

	bool nord;
	bool sud;
	bool ouest;
	bool sud;
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
			while(i < 5){
				if(pointOutsidePoly)
					nouveauPoint->x = pointDepart->x + distanceVoisin/diviseur;
				else
					nouveauPoint->x = pointDepart->x - distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}	
			if(pointIsInPoly(nouveauPoint, lePolygone) == true)
				cote_proche = true;

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y  + distanceVoisin;

			nord = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y - distanceVoisin;

			sud = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		if(pointIsInPoly(nouveauPoint, lePolygone) == true){
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				
				gen_point(lePolygone, nouveauPoint,cote_proche,nord&&cote_proche || !cote_proche,sud&&cote_proche || !cote_proche,!cote_proche,false);
				
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
			while(i < 5){
				if(pointOutsidePoly)
					nouveauPoint->x = pointDepart->x - distanceVoisin/diviseur;
				else
					nouveauPoint->x = pointDepart->x + distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}	
			if(pointIsInPoly(nouveauPoint, lePolygone) == true)
				cote_proche = true;

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y  + distanceVoisin;

			nord = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x;
			nouveauPoint2->y = pointDepart->y - distanceVoisin;

			sud = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		if(pointIsInPoly(nouveauPoint, lePolygone) == true){
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				
				gen_point(lePolygone, nouveauPoint,cote_proche,nord&&cote_proche || !cote_proche,sud&&cote_proche || !cote_proche,false,!cote_proche);
				
				nouveauPoint = init_point();
			}
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
			while(i < 5){
				if(pointOutsidePoly)
					nouveauPoint->y = pointDepart->y - distanceVoisin/diviseur;
				else
					nouveauPoint->y = pointDepart->y + distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}	
			if(pointIsInPoly(nouveauPoint, lePolygone) == true)
				cote_proche = true;

			nouveauPoint2->x = pointDepart->x - distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			ouest = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x + distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			est = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		if(pointIsInPoly(nouveauPoint, lePolygone) == true){
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				
				gen_point(lePolygone, nouveauPoint,cote_proche,!cote_proche,false,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche);
				
				nouveauPoint = init_point();
			}
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
			while(i < 5){
				if(pointOutsidePoly)
					nouveauPoint->y = pointDepart->y + distanceVoisin/diviseur;
				else
					nouveauPoint->y = pointDepart->y - distanceVoisin/diviseur;

				diviseur *= 2;
				pointOutsidePoly = !pointIsInPoly(nouveauPoint, lePolygone);
				i++;
			}	
			if(pointIsInPoly(nouveauPoint, lePolygone) == true)
				cote_proche = true;

			nouveauPoint2->x = pointDepart->x - distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			ouest = pointIsInPoly(nouveauPoint2, lePolygone);

			nouveauPoint2->x = pointDepart->x + distanceVoisin;
			nouveauPoint2->y = pointDepart->y;

			est = pointIsInPoly(nouveauPoint2, lePolygone);
		}
		if(pointIsInPoly(nouveauPoint, lePolygone) == true){
			existant = false;
			for(int i = 0; i < lePolygone->nbPoint && existant == false; i++){
				if(nouveauPoint->x == lePolygone->listePointPoly[i]->x && nouveauPoint->y == lePolygone->listePointPoly[i]->y){
					existant = true;
				}
			}
			if(!existant){
				lePolygone->listePointPoly = (point **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				
				gen_point(lePolygone, nouveauPoint,cote_proche,false,!cote_proche,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche);
				
				nouveauPoint = init_point();
			}
		}
	}

	
		


}






// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone(polygone* lePolygone, point* pointDepart, float distanceVoisin, char cote, float diff){
	if(pointIsInPoly(pointDepart, lePolygone) == false){
		return false;
	}
	lePolygone->listePointPoly = (point **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(point*));
	lePolygone->listePointPoly[lePolygone->nbPoint - 1] = pointDepart;
	gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin, cote, diff);
	return true;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point(polygone* lePolygone, point* pointDepart, float distanceVoisin, char cote, float diff){
	point* nouveauPoint = init_point();

	//Point à l'OUEST
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
			if(cote == 'O'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin - diff, cote, diff);
			}else if (cote == 'E'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin + diff, cote, diff);
			}else{
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin,, cote, diff);
			}
			nouveauPoint = init_point();
		}
	}

	//Point à l'EST
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
			if(cote == 'E'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin - diff, cote, diff);
			}else if (cote == 'O'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin + diff, cote, diff);
			}else{
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin,, cote, diff);
			}
			nouveauPoint = init_point();
		}
	}


	//Point au NORD
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
			if(cote == 'N'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin - diff, cote, diff);
			}else if (cote == 'S'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin + diff, cote, diff);
			}else{
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin,, cote, diff);
			}
			nouveauPoint = init_point();
		}
	}

	// Point au SUD
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
			if(cote == 'S'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin - diff, cote, diff);
			}else if (cote == 'N'){
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin + diff, cote, diff);
			}else{
				gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin,, cote, diff);
			}
		}
	}
}
void delete_point_temporaire(point* lePoly, point* lePolyInterdit){
	int id_premier_sommet = lePoly->id;

	point* sommet_courant = lePolygone;
	point* sommet_suivant = lePolygone->next;


	


	while(sommet_courant->id != id_premier_sommet){
		if(pointIsInPoly(sommet_courant, lePolyInterdit) == true){
			add_point_liste(lePolyInterdit, sommet_courant->x, sommet_courant->y);
			remove_point_liste(lePoly, sommet_courant->x, sommet_courant->y);
		}


		sommet_courant = sommet_suivant;
		sommet_suivant = sommet_suivant->next;
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

void delete_point2(polygone* lePoly, point* sommetPolyInterdit){
	polygone* polyInterdit = creerPolyInterdit(sommetPolyInterdit);
	for(int i = 0; i < lePoly->nbPoint; i++){
		if(pointIsInPoly(lePoly->listePointPoly[i], polyInterdit) == true){
			point* pointFree = lePoly->listePointPoly[i];
			if(i != lePoly->nbPoint - 1)
				lePoly->listePointPoly[i] = lePoly->listePointPoly[lePoly->nbPoint - 1];
			lePoly->listePointPoly = (point**)realloc(lePoly->listePointPoly, --(lePoly->nbPoint)*sizeof(point*));
			i--;
			free(pointFree);
		}
	}
	free(polyInterdit);
}

bool verif_Voisin(polygone* lePoly, point* depart, point* destination){
	bool verif = true;
	point * sommet1 = lePoly->sommetPoly;
	point * sommet2 = sommet1->next;

	//Nécessaire pour boucle
	int x = sommet2->x;
	int y = sommet2->y;
	for(int w = 0; (w < 1 && sommet2->x != x && sommet2->y !=y) || !verif ; w++){
		int a1 = (depart->y - destination->y)/ (depart->x - destination->x);
		int b1 = (depart->y - (a1*depart->x));

		int a2 = (sommet1->y - sommet2->y)/(sommet1->x - sommet2->x);
		int b2 = (sommet1->y - (a2*sommet1->x));

		if((a1 - a2) != 0){
			int m = (b2 - b1)/(a1 - a2);
			if(depart->x < destination->x){
				if(depart->x < m && destination->x > m){
					verif = !verif;
				}
			}else{
				if(depart->x > m && destination->x < m){
					verif = !verif;
				}
			}
		}
		sommet1 = sommet1->next;
		sommet2 = sommet2->next;
	}
	return verif;
}
