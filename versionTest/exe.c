#include "entree_kml.h"
#include "gen_graph.h"

#define distanceVoisinCreation 0.001

int main(int argc, char* argv[]){
	// Vérification des arguments
	if(argc < 2){
		printf("Erreur argument: ./exe export.kml\n");
		return 1;
	}

	// Variables
	liste_polygone* listeDepart = init_liste_polygone();
	pointp* sommetDepart;
	pointp* sommetEnCours;

	int nbPoly = 0;
	polygone** listePolygone = (polygone**)malloc(nbPoly*sizeof(polygone*));

	// Extraction du fichier KML
	sommetDepart = extraire_polygones(argv[1], listeDepart);

	// Vérification de l'export et mise en place dans les structures polygones
	if(sommetDepart != NULL){
		// Récupération de l'ensemble des polygones
		liste_polygone* liste = listeDepart;
		//Le premier élément de la listePolygone étant vide, on passe directement au second
		while(liste->next != NULL){
			liste = liste->next;
			sommetDepart = liste->polygone->next;
			if(sommetDepart->next != NULL){
				sommetEnCours = sommetDepart;
				while(sommetEnCours->next != NULL){
					sommetEnCours = sommetEnCours->next;
				}
				sommetEnCours->next = sommetDepart;
				listePolygone = (polygone**)realloc(listePolygone, ++(nbPoly)*sizeof(polygone*));
				listePolygone[nbPoly-1] = creerPoly(sommetDepart);
			}
		}

	}else{
		printf("Erreur extraction, fichier vide ou incorrect \n");
		return 1;
	}

	if(nbPoly == 0){
		printf("Problème lors de l'extraction, ou Polygone à un seul point \n");
		return 1;
	}else{
		if(gen_point_polygone(listePolygone[0], listePolygone[0]->sommetPoly, distanceVoisinCreation)){
			for(int i = 1; i < nbPoly; i++){
				delete_point_polygone(listePolygone[0], listePolygone[i]);
			}
			genererGraphe(listeDepart, listePolygone[0]);
		}else{
			printf("Génération impossible, point de départ en dehors du polygone \n");
		}
	}
	printf("Graphe générer dans tspp.dat \n");
	return 0;
}
