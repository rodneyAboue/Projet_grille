#include "entree_kml.h"
#include "structure_point_polygone.h"

int main(int argc,  char* argv[]){
	
	liste_polygone* liste = init_liste_polygone();
	pointp* depart;
	
	depart = extraire_polygones(argv[1], liste);
	
	printf("\n");
	printf("//----- RESULTAT----\n");
	printf("\n");
	
	if(depart!=NULL){
		printf("- point de depart -\n");
		printf("\n");
		afficher_liste_point(depart);
		delete_liste_point(depart);
		printf("\n");
	}
	
	printf("- polygones -\n");
	printf("\n");
	afficher_liste_polygone(liste);
	delete_liste_polygone(liste);

	return 0;
}
