#include "entree_kml.h"
#include "gen_graph.h"

int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Erreur argument: ./exe export.kml\n");
	}
	liste_polygone* liste = init_liste_polygone();
	printf("Liste de polygone initialisé \n");
	pointp* sommetDepart;
	sommetDepart = extraire_polygones(argv[1], liste);
	printf("Données du .kml extraite\n");
	if(sommetDepart != NULL){
		sommetDepart = ;
		do{
			printf("%f %f \n");
		}while(1);
		afficher_liste_polygone(liste);
	}
	return 0;
}
