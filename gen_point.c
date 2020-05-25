#include "gen_point.h"

polygone * creerPoly(pointp * unSommet){
	polygone * lePoly = (polygone*)malloc(1*sizeof(polygone));
	lePoly->nbPoint = 0;
	lePoly->sommetPoly = unSommet;
	lePoly->listePointPoly=(pointp**)malloc(lePoly->nbPoint*sizeof(pointp*));
	lePoly->type = 's';
	return lePoly;
}

polygone* creerPolyInterdit(pointp* unSommet){
	polygone * lePoly = creerPoly(unSommet);
	lePoly->type = 'i';
	return lePoly;
}

// Vérifier que le point se trouve dans le polygone
bool pointIsInPoly(pointp* lePoint, polygone* lePolygone){
	bool isInside = false;
	float minX, minY, maxX, maxY;
	minX = lePolygone->sommetPoly->x;
	minY = lePolygone->sommetPoly->y;
	maxX = minX;
	maxY = minY;
	//Recuperer le maximum et minimum des coordonnées x/y
	pointp* sommetSuivant = lePolygone->sommetPoly->next;
	while(sommetSuivant->x != lePolygone->sommetPoly->x || sommetSuivant->y != lePolygone->sommetPoly->y){
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
	if(lePoint->x < minX || lePoint->x > maxX){
		return false;
	}
	if(lePoint->y < minY || lePoint->y > maxY){
		return false;
	}
	//printf("Min/Max validé \n");

	//Vérif si il est bien à l'intérieur
	pointp * sommet1 = lePolygone->sommetPoly;
	pointp * sommet2 = sommet1->next;
	//Nécessaire pour boucle
	float x = sommet2->x;
	float y = sommet2->y;
	int compteur = 0;
	pointp* depart = lePoint;
	pointp* destination = init_point();
	destination->x = minX - 5; destination->y = minY-5;

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
							compteur++;
						}
					}

				}else{
					if(depart->x < m && destination->x > m){
						if(sommet1->x > m && sommet2->x < m){
							compteur++;
						}
					}
				}
			}else {
				if(sommet1->x < sommet2->x){
					if(depart->x > m && destination->x < m){
						if(sommet1->x < m && sommet2->x > m){
							compteur++;
						}
					}

				}else{
					if(depart->x > m && destination->x < m){
						if(sommet1->x > m && sommet2->x < m){
							compteur++;
						}
					}
				}
			}
		}
		sommet1 = sommet1->next;
		sommet2 = sommet2->next;
	}
	//printf("Compteur: %d \n", compteur);
	if(compteur%2==0){
		return false;
	}
	return true;

}

// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone_TEMPORAIRE(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	if(pointIsInPoly(pointDepart, lePolygone) == false){
		return false;
	}
	lePolygone->listePointPoly = (pointp **) realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
	lePolygone->listePointPoly[0] = pointDepart;
	gen_point_TEMPORAIRE(lePolygone, pointDepart,false,true,true,true,true, distanceVoisin);
	return true;
}

// Générer l'ensemble des points à partir d'un point de départ
void gen_point_TEMPORAIRE(polygone* lePolygone, pointp* pointDepart, bool point_sur_arrete,bool explorer_nord, bool explorer_sud, bool explorer_ouest, bool explorer_est, float distanceVoisin){
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
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,nord&&cote_proche || !cote_proche,sud&&cote_proche || !cote_proche,false,!cote_proche, distanceVoisin);
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
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,!cote_proche,false,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche, distanceVoisin);
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
				lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
				lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
				gen_point_TEMPORAIRE(lePolygone, nouveauPoint,cote_proche,false,!cote_proche,ouest&&cote_proche || !cote_proche,est&&cote_proche || !cote_proche, distanceVoisin);
				nouveauPoint = init_point();
			}
		}
	}

}






// Vérifier le point de départ et lancer ensuite la création des points
bool gen_point_polygone(polygone* lePolygone, pointp* pointDepart, float distanceVoisin){
	if(!pointIsInPoly(pointDepart, lePolygone)){
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
	if(pointIsInPoly(nouveauPoint, lePolygone) == true){
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
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
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
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
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
			lePolygone->listePointPoly = (pointp **)realloc(lePolygone->listePointPoly, ++(lePolygone->nbPoint)*sizeof(pointp*));
			lePolygone->listePointPoly[lePolygone->nbPoint - 1] = nouveauPoint;
			gen_point(lePolygone, lePolygone->listePointPoly[lePolygone->nbPoint-1], distanceVoisin);
		}
	}
}

void delete_point_polygone(polygone* lePoly, polygone* lePolyInterdit){
	for(int i = 0; i< lePoly->nbPoint; i++){
		if(pointIsInPoly(lePoly->listePointPoly[i], lePolyInterdit) == true){
			lePolyInterdit->listePointPoly = (pointp**)realloc(lePolyInterdit->listePointPoly, ++(lePolyInterdit->nbPoint)*sizeof(pointp*));
			lePolyInterdit->listePointPoly[lePolyInterdit->nbPoint-1] = lePoly->listePointPoly[i];
			for(int j = i; j < lePoly->nbPoint -1; j++){
				lePoly->listePointPoly[j] = lePoly->listePointPoly[j+1];
			}
			lePoly->listePointPoly = (pointp**)realloc(lePoly->listePointPoly, --(lePoly->nbPoint)*sizeof(pointp*));
			i--;
		}
	}
}

void delete_point_polygone2(polygone* lePoly, pointp* sommetPolyInterdit){
	polygone* polyInterdit = creerPolyInterdit(sommetPolyInterdit);
	for(int i = 0; i < lePoly->nbPoint; i++){
		if(pointIsInPoly(lePoly->listePointPoly[i], polyInterdit)){
			pointp* pointFree = lePoly->listePointPoly[i];
			lePoly->listePointPoly[i] = lePoly->listePointPoly[lePoly->nbPoint - 1];
			lePoly->listePointPoly = (pointp**)realloc(lePoly->listePointPoly, --(lePoly->nbPoint)*sizeof(pointp*));
			free(pointFree);
		}
	}
	free(polyInterdit);
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
