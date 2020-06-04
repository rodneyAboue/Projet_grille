#include "structure_point_polygone.h"
#include "entree_kml.h"
#include "dislin.h"

//attention cette version n'est pas complète

int main(){
	
	liste_polygone* liste = init_liste_polygone();	
	pointp* depart, *visites, *vus, *non_vus;
	depart = extraire_polygones( "test_io_export.kml", liste);
	puts("entree : ok\n");
	
	visites = liste->next->next->polygone;
	vus = liste->next->next->next->polygone;
	non_vus = liste->next->next->next->next->polygone;
	
	pointp* l1 = init_sommet();
	pointp* l2 = init_sommet();
	
	draw_probleme(liste, l1);

	draw_resultat(liste, visites, vus, non_vus);
	
	return 0;

}
