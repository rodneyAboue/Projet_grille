#include "gen_point.h"

int main(){
	printf("Début des tests\n");
	pointp * sommet1 = init_point();
	sommet1->x = 1;
	sommet1->y = 1;

	pointp * sommet2 = init_point();
	sommet2->x = 1;
	sommet2->y = 11;

	pointp * sommet3 = init_point();
	sommet3->x = 11;
	sommet3->y = 11;

	pointp * sommet4 = init_point();
	sommet4->x = 11;
	sommet4->y = 1;

	sommet1->next = sommet2;
	sommet2->next = sommet3;
	sommet3->next = sommet4;
	sommet4->next = sommet1;

	pointp* sommetActuel = sommet1;
	printf("Test de la boucle next\n");
	for(int j = 0; j<1 || sommetActuel-> x != sommet1->x || sommetActuel->y != sommet1->y; j++){
		printf("x=%f y=%f\n", sommetActuel->x, sommetActuel->y);
		sommetActuel = sommetActuel->next;
	}
	free(sommetActuel);
	printf("Fin du test de la boucle next\n");

	printf("Test de la fonction creerPoly(pointp*)\n");
	polygone* poly1 = creerPoly(sommet1);
	if(poly1->sommetPoly->x == 1 && poly1->sommetPoly->y == 1 && poly1->type == 's' && poly1->nbPoint == 0){
		printf("Test basique réussi \n");
	}else{
		printf("Test basique raté\n");
	}

	printf("Fin des tests\n");
	return 0;
}
