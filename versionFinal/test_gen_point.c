#include "gen_point.h"
#include "gen_graph.h"


liste_polygone* polygones;

int main(){
	printf("Début des tests\n");
	pointp * sommet1 = init_point();
	sommet1->x = 0;
	sommet1->y = 0;

	pointp * sommet2 = init_point();
	sommet2->x = 10;
	sommet2->y = 0;

	pointp * sommet3 = init_point();
	sommet3->x = 10;
	sommet3->y = 10;

	pointp * sommet4 = init_point();
	sommet4->x = 0;
	sommet4->y = 10;

	sommet1->next = sommet2;
	sommet2->next = sommet3;
	sommet3->next = sommet4;
	sommet4->next = sommet1;

	printf("---------------\n");
	printf("Test de la boucle next\n");
	pointp* sommetActuel = sommet1;
	for(int j = 0; j<1 || sommetActuel-> x != sommet1->x || sommetActuel->y != sommet1->y; j++){
		printf("x=%f y=%f\n", sommetActuel->x, sommetActuel->y);
		sommetActuel = sommetActuel->next;
	}
	printf("Fin du test de la boucle next\n");

	printf("Test de la fonction creerPoly(pointp*)\n");
	polygone* poly1 = creerPoly(sommet1);
	if(poly1->sommetPoly->x == 0 && poly1->sommetPoly->y == 0 && poly1->type == 's' && poly1->nbPoint == 0){
		printf("Test basique réussi \n");
	}else{
		printf("Test basique raté\n");
	}

	printf("---------------\n");
	printf("Test de la fonction isInside(pointp*, polygone*) \n");
	pointp* test = init_point();
	test->x = 5;
	test->y = 5;
	if(isInside(test, poly1)){
		printf("Test basique réussi\n");
		test->x = 11;
		test->y = 15;
		if(!isInside(test, poly1)){
			printf("Test avancé réussi\n");
		}else{
			printf("Test avancé raté\n");
		}
	}else{
		printf("Test basique raté \n");
	}

	sommet1->next = sommet2;
	sommet2->next = sommet3;
	sommet3->next = sommet4;
	sommet4->next = sommet1;


	polygones = init_liste_polygone();

	

	add_polygone_liste(polygones, sommet1);

	//afficher_liste_polygone(polygones);






	


	printf("---------------\n");
	printf("Début des tests de gen_point_polygone (et donc de gen_polygone)\n");
	test->x = 15;
	test->y = 22;
	if(!gen_point_polygone(poly1, test, 1)){
		printf("Test basique réussi\n");
		test->x = 6;
		test->y = 4;
		if(gen_point_polygone(poly1, test, 1)){
			printf("Test avancé réussi\n");
			for(int i = 0; i < poly1->nbPoint;i++){
				printf("Point n°%d: x=%f y=%f\n", i+1, poly1->listePointPoly[i]->x, poly1->listePointPoly[i]->y);
			}
		}else{
			printf("Test avancé raté\n");
		}
	}else{
		printf("Test basique raté\n");
	}

	genererGraphe_SECOUR(poly1);



	printf("Fin des tests\n");
	return 0;
}
