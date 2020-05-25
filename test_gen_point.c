#include "gen_point.h"

int main(){
	printf("Début des tests\n");
	pointp * sommet1 = init_point();
	sommet1->x = 1;
	sommet1->y = 1;

	pointp * sommet2 = init_point();
	sommet2->x = 2;
	sommet2->y = 8;

	pointp * sommet3 = init_point();
	sommet3->x = 8;
	sommet3->y = 9;

	pointp * sommet4 = init_point();
	sommet4->x = 9;
	sommet4->y = 2;

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
	if(poly1->sommetPoly->x == 1 && poly1->sommetPoly->y == 1 && poly1->type == 's' && poly1->nbPoint == 0){
		printf("Test basique réussi \n");
	}else{
		printf("Test basique raté\n");
	}

	printf("---------------\n");
	printf("Test de la fonction pointIsInPoly(pointp*, polygone*) \n");
	pointp* test = init_point();
	test->x = 5;
	test->y = 7;
	if(pointIsInPoly(test, poly1)){
		printf("Test basique réussi\n");
		sommet2->next = sommet4;
		sommet3->next = sommet1;
		sommet1->next = sommet2;
		sommet4->next = sommet3;
		if(!pointIsInPoly(test, poly1)){
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
	printf("---------------\n");
	printf("Début des tests de gen_point_polygone (et donc de gen_polygone)\n");
	test->x = 0;
	test->y = 0;
	if(!gen_point_polygone(poly1, test, 1)){
		printf("Test basique réussi\n");
		test->x = 5;
		test->y = 7;
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
	printf("---------------\n");
	printf("Début des tests delete_point_polygone \n");
	pointp* s5 = init_point();
	pointp* s6 = init_point();
	pointp* s7 = init_point();

	s5->x = 1; s6->x= 2; s7->x = 8;
	s5->y = 1; s6->y=8; s7->y = 9;
	s5->next = s6;
	s6->next = s7;
	s7->next = s5;
	int nombrePrecedent = poly1->nbPoint;
	delete_point_polygone2(poly1, s5);
	if(poly1->nbPoint != nombrePrecedent){
		printf("Test réussi \n");
		for(int i = 0; i < poly1->nbPoint; i++){
			printf("Point n°%d: x=%f y=%f \n", i+1, poly1->listePointPoly[i]->x, poly1->listePointPoly[i]->y);
		}
	}else{
		printf("Test raté\n");
	}

	printf("Fin des tests\n");
	return 0;
}
