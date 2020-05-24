#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "structure_point_polygone.h"

int id_point = 0; 

#define MY_PREC 0.0005

//--------------POLYGONE----------------------

liste_polygone* init_liste_polygone(){
	liste_polygone* p;
	p = (liste_polygone *) malloc(sizeof(liste_polygone));
	
	if(p==NULL){
		perror("erreur malloc");
		exit(1);
	}
	
	p->polygone = init_point();
	
	return p;
}



void add_polygone_liste(liste_polygone* liste, point* p){
	
	if(liste == NULL || p == NULL){
		perror("erreur parametre null");
		exit(2);
	}
	
	
	while(liste->next != NULL){
		liste = liste->next;
	}
	
	liste->next = init_liste_polygone();
	
	liste->next->polygone = p;
	
}

void afficher_liste_polygone(liste_polygone* lp){
	
	if(lp == NULL){
		perror("erreur parametre null");
		exit(2);
	}
	printf("liste polygone = {\n");
		
	while(lp->next != NULL){		
		afficher_liste_point(lp->next->polygone);
		lp = lp->next;
	}
	printf("}\n");
}

void delete_liste_polygone(liste_polygone* lp){

	if(lp == NULL){
		perror("erreur parametre null");
		exit(2);
	}	
	
	if(lp->next != NULL){
		lp = lp->next;
		delete_liste_polygone(lp);
		delete_liste_point(lp->polygone);
	}
	
}

//-------------------- FONCTIONS ASSOCIEES --------------------

//initialise un point 
//lui donne un id unique et alloue la liste des voisins
//renvoie le pointeur passé en paramètre 
point* init_point(){
	point* p;
	p = (point*) malloc(sizeof(point));
	if(p==NULL){
		perror("erreur malloc");
		exit(1);
	}
	return p;
}

void delete_point(point* p){
	
	if(p==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	free(p);
}

//affiche un point sous le format : 
//- id < x,y >\n
void afficher_point(point *p){

	if(p==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	printf("- %d < %f,%f >\n", p->id, p->x, p->y);
}

//revoie le nombre d'éléments d'une liste 
int count_point_liste(point* liste){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	return compte_point_liste_2(liste, 0);
}

int compte_point_liste_2(point* liste, int nb_pts){

	nb_pts = nb_pts+1;
	
	if(liste->next == NULL){
		return nb_pts;
	} 
	else{
		return compte_point_liste_2(liste->next, nb_pts);
	}
}

// renvoie le pointeur du point
// renvoie NULL si le point n'est pas trouve
point* search_point_liste_id(point* liste, int id){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	while(liste->next != NULL){
		if(liste->id == id) return liste;
		liste = liste->next;
	}
	return NULL;
};

// renvoie le pointeur du point
// renvoie NULL si le point n'est pas trouve
point* search_point_liste_coords(point* liste, double x, double y){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	while(liste->next != NULL){
		//if(liste->x == x && liste->y == y) return liste;
		
		if(liste->x <= x + MY_PREC && liste->x >= x - MY_PREC && liste->y <= y + MY_PREC && liste->y >= y - MY_PREC) return liste;
	
		
		liste = liste->next;
	}
	return NULL;
};

//ajoute un point à une liste de points
//revoie l'id du point ajouté 
// ou -1 si le point est déjà présent dans la liste
int add_point_liste(point* liste, double x, double y){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	/*
	point* p;
	p=init_point(p);
	p->x = x;
	p->y = y;
	p->id = id_point++;
	*/
	
	while(liste->next != NULL){
		if(liste->next->x == x && liste->next->y == y) return -1;
		
		liste = liste->next;
	}
	
	liste->next = init_point();
	liste->next->x = x;
	liste->next->y = y;
	liste->next->id = ++id_point;
	
	return liste->next->id;
	//return p->id;
};

//retire un point à une liste de points
//revoie 0 si le point est retiré 
// ou -1 si le point n'est pas présent dans la liste
int remove_point_liste(point* liste, double x, double y){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}		
		
	while(liste->next != NULL){
		if(liste->next->x == x && liste->next->y == y) {
			point* del = liste->next;
			liste->next = del->next;
			delete_point(del);
			return 0;
		}
		liste = liste->next;
	}
	
	return -1;
};	

//supprime une liste de points et libère sa composante liste
void delete_liste_point_rec(point* liste){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	if(liste->next != NULL)
		delete_liste_point_rec(liste->next);
	
	liste->next = NULL;
	delete_point(liste);
};

void delete_liste_point(point* liste){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	if(liste->next != NULL)
		delete_liste_point_rec(liste->next);
	
	liste->next = NULL;
};


//affiche une liste de points
void afficher_liste_point_rec(point* liste){

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	if(liste->next != NULL){
		afficher_point(liste->next);
		afficher_liste_point_rec(liste->next);
	}
};

void afficher_liste_point(point* liste){

	point* it = liste;

	if(liste==NULL){
		perror("error parametre null");
		exit(2);
	}
	
	printf("liste = {\n");
	if(liste->next != NULL){
		afficher_point(liste->next);
		afficher_liste_point_rec(liste->next);
	}
	printf("};\n");
	printf("\n");
};





