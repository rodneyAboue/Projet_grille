#include "gen_graph.h"

// Variable correspondant aux distances entre 2 points pour considerer qu'un point est voisin à un autre ou couvert
#define distanceCouverture 0.005
#define distanceVoisin 0.01

/*
* Vérifie si le segment entre les points lePolygone->listePointPoly[i] et lePolygone->listePointPoly[j] croise une arete de l'un des polygones
*/
bool intersection(polygone *lePolygone, int i, int j, liste_polygone* polygones){
	liste_polygone* lesPolygones = polygones;
	pointp* sommet;
	// Parcours de l'ensemble des polygones contenu dans la liste (Premier polygone vide)
	while(lesPolygones->next != NULL){
		lesPolygones = lesPolygones->next;
		sommet = lesPolygones->polygone;
		// pour chaque arrête [sommet sommet->next] du polygone
		while(sommet != lesPolygones->polygone){
			if(doIntersect(lePolygone->listePointPoly[i], lePolygone->listePointPoly[j], sommet, sommet->next)){
				return true;
			}
			sommet = sommet->next;
		}
	}
	return false;
}

/*
* Génération du graphe
* Insère l'ensemble des couples voisins/vus dans un fichier .dat
*/
void genererGraphe(liste_polygone* lesPolygones, polygone* lePolygone){
	bool accesDirect;
	float distance;

	// Création du fichier tspp.dat en supprimant une ancienne version si le fichier existe déjà
	FILE * fichier = fopen("tspp.dat", "w");
	fprintf(fichier ,"alpha=0.5;\n");
	fprintf(fichier ,"n=%d;\n",lePolygone->nbPoint);

	// Mise en place des voisins
	fprintf(fichier ,"Edges= {\n");
	for(int i = 0; i < lePolygone->nbPoint; i++){
		for(int j = i + 1; j < lePolygone->nbPoint; j++){
			distance = sqrtf(pow((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x),2) + pow((lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y),2));
			accesDirect = !intersection(lePolygone, i, j, lesPolygones);
			if(distance <= distanceVoisin && accesDirect){
				fprintf(fichier, "< %d %d >,\n", lePolygone->listePointPoly[i]->id, lePolygone->listePointPoly[j]->id);
			}
		}
	}
	fseek(fichier, -2, SEEK_END); // Retire la dernière virgule
	fprintf(fichier, "\n};\n");

	// Mise en place des points couverts
	fprintf(fichier, "CoveredBy = [\n");
	for(int i = 0; i < lePolygone->nbPoint; i++){
		fprintf(fichier, "{ ");
		for(int j = 0; j< lePolygone->nbPoint; j++){
			distance = sqrtf(pow((lePolygone->listePointPoly[i]->x - lePolygone->listePointPoly[j]->x),2) + pow((lePolygone->listePointPoly[i]->y - lePolygone->listePointPoly[j]->y),2));
			accesDirect = !intersection(lePolygone, i, j, lesPolygones);
			if(distance <= distanceCouverture && accesDirect){
				fprintf(fichier, "%d, ", lePolygone->listePointPoly[j]->id);
			}
		}
		fseek(fichier, -2, SEEK_END);
		fprintf(fichier, " },\n");
	}
	fseek(fichier, -2, SEEK_END);
	fprintf(fichier, "\n];\n");
	fclose(fichier);
}
