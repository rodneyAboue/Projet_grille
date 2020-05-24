#include "gen_point.h"

int main(){
	point * sommet1 = init_point();
	sommet1->x = 1;
	sommet1->y = 1;
	
	point * sommet2 = init_point();
	sommet2->x = 1;
	sommet2->y = 11;
	
	point * sommet3 = init_point();
	sommet3->x = 11;
	sommet3->y = 1;
	
	point * sommet4 = init_point();
	sommet4->x = 11;
	sommet4->y = 11;
	


	return 0;
}
