#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "structure_point_polygone.h"

//avance le curseur à la balise <coordinates> suivant
// = le debut des coordonnées d'un polygone
//retourne 1 si il y en a une
// 0 sinon
int next_polygone(FILE* f){
	int ok = 0;
	char c = '\0';
	while(ok==0 && c != EOF){
		c = fgetc(f);
		if(c=='<'){
			c = fgetc(f);
			if(c=='c'){
				c = fgetc(f);
				if(c=='o'){
					c = fgetc(f);
					if(c=='o'){
						c = fgetc(f);
						if(c=='r'){
							c = fgetc(f);
							if(c=='d'){
								c = fgetc(f);
								if(c=='i'){
									c = fgetc(f);
									if(c=='n'){
										c = fgetc(f);
										if(c=='a'){
											c = fgetc(f);
											if(c=='t'){
												c = fgetc(f);
												if(c=='e'){
													c = fgetc(f);
													if(c=='s'){
														c = fgetc(f);
														if(c=='>'){
															ok = 1;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return ok;
}
//prend en parametre un FILE* d'un export kml
//retourne le polygone présen à la suite du curseur de parcours du ficher
pointp* create_polygone(FILE* f){
	pointp* py = init_sommet();
	double x, y;
	int fin = 0;
	while(!fin){
		if(fscanf(f, "%lf,%lf", &x, &y)==0){
			perror("erreur fscanf\n");
			exit(2);
		}
		add_point_liste(py, x, y);
		if(fgetc(f)!= ' ') fin =1;
	}
	return py;
}


//prend en entrée un export.kml de data.shom et une liste de polygone vide mais initialisée
//extraire polygone remplit la liste de polygone avec ceux detectes dans le .kml
//et retourne un pointeur vers le point de depart si il a ete detecte, NULL sinon 
pointp* extraire_polygones(const char* export, liste_polygone* liste){

	FILE* f = fopen( export, "r"); 
	if(f==NULL){
		perror("erreur fopen");
		exit(1);
	}

	int fin = 0;
	pointp* py, *depart = NULL;

	//boucle de creation
	while(1){
		if (next_polygone(f) == 0)
			break;
		py = create_polygone(f);
		//point de depart à mettre au point
		if(py->next->next == NULL){
			if(depart != NULL){
				perror("erreur entree : points de depart multiples\n");
				exit(3);
			}
			depart = py;
		} else {
			add_polygone_liste(liste, py);		}
	}
	return depart;
}

/*
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
*/









