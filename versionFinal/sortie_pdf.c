#ifndef SORTIE_PDF
#define SORTIE_PDF

#include <stdlib.h>
#include <stdio.h>
#include "dislin.h"
#include "structure_point_polygone.h"

//-----FONCTIONS INTERNES-----

// releve les extremums des coordonnées d'une liste de points
//prend en parametre la liste de touts les points et les pointeurs des retours
void def_bornes(pointp* liste, float* xmin, float* xmax, float* xpas, float* ymin, float* ymax, float* ypas){

	if(liste==NULL || xmin==NULL || xmax==NULL || xpas==NULL || ymin==NULL || ymax==NULL || ypas==NULL){
		perror("def_bornes parametre null\n");
		exit(1);
	}

	double xmi, xma, ymi, yma;
	xmi = liste->next->x;
	xma = liste->next->x;
	ymi = liste->next->y;
	yma = liste->next->y;
	
	liste = liste->next;

	while(liste->next!=NULL){
		if(xmi > liste->next->x) xmi = liste->next->x;
		if(xma < liste->next->x) xma = liste->next->x;
		if(ymi > liste->next->y) ymi = liste->next->y;
		if(yma < liste->next->y) yma = liste->next->y;
		
	liste = liste->next;
	}
	
	*xmin = (float)xmi; 
	*xmax = (float)xma;
	*ymin = (float)ymi;
	*ymax = (float)yma;
	
	*xpas = (xma-xmi)/5.;
	*ypas = (yma-ymi)/5.;
}

int init_coord_array(float** coord_x, float** coord_y, pointp* liste){

	if(liste->next == NULL){
		perror("parametre null");
		exit(2);
	}

	int i=0;
	
	int size = count_point_liste(liste);
	
	pointp* it = liste;
	
	*coord_x = (float*) malloc((size) * sizeof(float));
	*coord_y = (float*) malloc((size) * sizeof(float));
	
	if(coord_x == NULL || coord_y == NULL){
		perror("erreur malloc");
		exit(2);
	}

	while(it->next != NULL){
	
		(coord_x[0][i]) = (float) it->next->x;
		(coord_y[0][i]) = (float) it->next->y;
		
		i=i+1;	
		it=it->next;
	}
	
	(coord_x[0][i]) = (float) liste->next->x;
	(coord_y[0][i]) = (float) liste->next->y;
	
	return size;

}

void delete_coord_array(float**coord_x, float** coord_y){
	free(*coord_x);
	free(*coord_y);
}

//initialise dislin et le sortie
void init_sortie_probleme(){

	metafl ("PDF");
	setfil("grille_out_probleme.pdf");
	disini();	
	
	//noms d'axes et titre
	name ("Longitude", "x");
  	name ("Latitude", "y");
  	titlin ("PROBLEME", 1);
}

void init_sortie_resultat(){

	metafl ("PDF");
	setfil("grille_out_resultat.pdf");
	disini();	
	
	//noms d'axes et titre
	name ("Longitude", "x");
  	name ("Latitude", "y");
  	titlin ("RESULTAT", 1);
  	titlin ("noir = visite, gris = vu, rouge = non_vu", 3);
}

float points_non_vus_percent(pointp* liste_globale, pointp* liste_non_vus){
	
	if(liste_globale == NULL || liste_non_vus == NULL){
		perror("draw_liste parametre null\n");
		exit(1);
	}

	float pc = ((float) count_point_liste(liste_non_vus) * 100.0)/(float) count_point_liste(liste_globale);
	
	return pc;

}

//dessine un point
//forme doit etre entre 0 et 23
//exemple forme : 4 cross, 21 dot, 15 circle, 21 filled circle
void draw_point(pointp* p, int forme){

	if(p==NULL){
		perror("draw_point parametre null\n");
		exit(1);
	}
	
	if(forme<0 || forme>23){
		perror("draw_point forme inconnue\n");
		exit(1);
	}
	
	rlsymb(forme, p->x, p->y);
};

//dessine une liste de points 
//forme doit etre entre 0 et 23
//exemple forme : 4 cross, 21 dot, 15 circle, 21 filled circle
void draw_liste_point(pointp* liste, int forme){

	if(liste==NULL){
		perror("draw_liste parametre null\n");
		exit(1);
	}
	
	if(forme<0 || forme>23){
		perror("draw_liste forme inconnue\n");
		exit(1);
	}
	
	while(liste->next!=NULL){
		draw_point(liste->next, forme);
		liste = liste->next;
	}
}

//dessine un polygone
void draw_polygone(pointp* py, char* couleur){

	if(py==NULL){
		perror("draw_polygone parametre null\n");
		exit(1);
	}
	
	
	float *coord_x, *coord_y; //tableaux de coordonnées pour la fonction curve
	int size;

	size = init_coord_array(&coord_x, &coord_y, py);

	color(couleur);
	curve(coord_x, coord_y, size); // tracé des courbes
	
	delete_coord_array(&coord_x, &coord_y);
}

//dessine une liste de polygone
void draw_liste_polygone(liste_polygone* liste, char* couleur){

	if(liste==NULL){
		perror("draw_liste_polygone parametre null\n");
		exit(1);
	}
	
	while(liste->next!=NULL){
		liste = liste->next;
		draw_polygone(liste->polygone, couleur);
	}
}

//dessine les polygones et la grille
void draw_probleme(liste_polygone* lp, pointp* grille){

	if(lp==NULL || grille==NULL){
		perror("sortie parametre null\n");
		exit(1);
	}

	float xmin, xmax, ymin, ymax, xpas, ypas; 

	init_sortie_probleme();	

	//cadrage du graph en fonction du polygone englobant
	def_bornes(lp->next->polygone, &xmin, &xmax, &xpas, &ymin, &ymax, &ypas);
	graf(xmin-xpas, xmax+xpas, xmin-xpas, xpas, ymin-ypas, ymax+ypas, ymin-ypas, ypas);

	//dessin des polygones
	lp=lp->next;
	draw_polygone(lp->polygone, "blue"); //polygone englobant en bleu	
	/* hs : les polygones sont invisible/tracés en blanc?
	if(lp->next != NULL)
		draw_liste_polygone(lp->next, "black"); //polygones interdits en noir
	*/
	
	//dessin des points
	hsymbl (20);
	color("black");
	draw_liste_point( grille, 4); // points = croix noires
	
	title();
	disfin();

}

//dessine les polygones, les points et le chemin à emprunter
void draw_resultat(liste_polygone* lp, pointp* visites, pointp* vus, pointp* non_vus){

	if(lp==NULL || visites==NULL || vus==NULL || non_vus ==NULL){
		perror("sortie parametre null\n");
		exit(1);
	}

	float xmin, xmax, ymin, ymax, xpas, ypas;

	init_sortie_resultat();

	//cadrage du graph en fonction du polygone englobant
	def_bornes(lp->next->polygone, &xmin, &xmax, &xpas, &ymin, &ymax, &ypas);
	graf(xmin-xpas, xmax+xpas, xmin-xpas, xpas, ymin-ypas, ymax+ypas, ymin-ypas, ypas);

	//dessin des polygones
	lp=lp->next;
	draw_polygone(lp->polygone, "blue"); //polygone englobant en bleu	
	/* hs : les polygones sont invisible/tracés en blanc?
	if(lp->next != NULL)
		draw_liste_polygone(lp->next, "black"); //polygones interdits en noir
	*/
	
	//dessin du chemin
	draw_polygone(visites, "green");

	//dessin des points
	hsymbl (20);
	
	draw_liste_point( visites, 4); // points visites = croix noires
	color("gray");
	draw_liste_point(vus, 4); //points vus = croix grises
	color("red");
	draw_liste_point(non_vus, 4); // points non vus = croix rouges
	
	color("black");
	title();
	disfin();

}

#endif




