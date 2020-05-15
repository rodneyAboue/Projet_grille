#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "structure_point_polygone.h"


#define TAILLE_MAX_LISTE_POINT 256
#define TAILLE_MAX_LISTE_POLYGONE 256

int id_point = 1;
int id_polygone = 1;

void init_point(point* p){

	if(p == NULL){
		perror("init_point");
		exit(2);
	}

	p->id = id_point;
	id_point = id_point+1;
	
	p->x = 0;
	p->y = 0;
	
	p->etat = '_';
	
	//p->voisins.liste = (point*) malloc(TAILLEMAX_LISTE_POINT * sizeof(point));
	
	init_liste_point(&(p->voisins));	
	
	if(p->voisins.liste == NULL){
		// il y a eu un probleme d'allocation
		perror("init_point");
		exit(1);
	}
	
}
/*---------*/

int remove_point_liste(liste_point* l, point* v){

	if(l == NULL || v == NULL){
		perror("remove_point_liste");
		exit(2);
	}

	int index, i, id;
	
	if((index = contient_point_liste(l, v)) == -1){	
		return -1;		
	}
	
	id = l->liste[index]->id;
	
	if(index == l->nb_point){
		// si l'element a supprimer est au bout de la liste
		l->nb_point = l->nb_point-1;
	}
	else{
		for(i=index; i<l->nb_point; i++){
			l->liste[i] = l->liste[i+1];			
		}
		l->nb_point = l->nb_point-1;
	}
	
	return id;
}

/*---------*/

void delete_point(point* p){

	int i;

	if(p==NULL){
		perror("delete_point");
		exit(2);
	}
	/*
	for(i=0; i<p->voisins.nb_point; i++){
		free(p->voisins.liste[i];
	}
	*/
	delete_liste_point(&(p->voisins));
	//free(p->voisins.liste);

}

/*--------------------------------------------------------------------*/

void init_liste_point(liste_point* l){

	if(l == NULL){
		perror("init_liste_point");
		exit(2);
	}

	l->nb_point = 0;
	l->liste = malloc(TAILLE_MAX_LISTE_POINT * sizeof(point*));
	
		if(l->liste == NULL){
		// il y a eu un probleme d'allocation
		perror("init_liste_point");
		exit(1);
	}
	
}
/*---------*/
int contient_point_liste(liste_point* l, point* v){

	if(l == NULL || v == NULL){
		perror("contient_point_liste");
		exit(2);
	}
	
	int i;
	
	if(l->nb_point == 0){
		return -1;
	}
	
	for(i=0; i<l->nb_point; i++){
		
		if( l->liste[i]->id == v->id){
			// le point est deja present
			return i;
		}	
	}
	
	return -1;
}

/*---------*/

int add_point_liste(liste_point* l, point* v){

	if(l == NULL || v == NULL){
		perror("add_point_liste");
		exit(2);
	}

	if(contient_point_liste(l, v) != -1){
		return -1;
	}	
	
	if(l->nb_point == TAILLE_MAX_LISTE_POINT){
	//la liste est pleine					
		return -2;		
	}	
	else{
		// ajout du point
		l->liste[l->nb_point] = v;
		l->nb_point = l->nb_point+1;
		return l->nb_point;
	}
	
}
/*---------*/
void delete_liste_point(liste_point* l){

	if(l==NULL){
		perror("delete_liste_point");
		exit(2);
	}
	
	int i;
	
	free(l->liste);
}

/*--------------------------------------------------------------------*/

void afficher_point(point *p){
	
	if(p == NULL){
		perror("afficher_point");
		exit(2);
	}
	
	int i;
	
	printf("-----------------------\n");
	printf("ID : %d, etat : %c \n", p->id, p->etat);
	printf("x : %f, y : %f \n", p->x, p->y);
	printf(" Voisin(s) (%d) : ", p->voisins.nb_point);
	if(p->voisins.nb_point == 0){
		printf("Pas de voisins");
	}
	else{
		for(i=0; i<p->voisins.nb_point; i++){
			printf(" %d ", p->voisins.liste[i]->id);
		}
	}
	printf("\n");
}

/*---------*/

void afficher_liste_point(liste_point* l){
	
	if(l == NULL){
		perror("afficher_liste_point");
		exit(2);
	}
	
	int i; 
	if(l->nb_point == 0){
		printf("liste vide\n");
	}
	else{
		for(i=0; i<l->nb_point; i++){
			afficher_point(l->liste[i]);
		}
		printf("\n");
	}
}

/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/



//---------- POLYGONE ----------

//initialise un polygone et lui donne un id unique
void init_polygone(polygone* py){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	py->id = id_polygone++;

	init_liste_point(&(py->sommets));
}

//teste la présence d'un point dans le polygone
//renvoie l'index si il est présent
//-1 sinon
int contient_point_polygone(polygone* py, point*p){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(p==NULL){
		perror("error parametre null");
		exit(2);
	}

	return contient_point_liste(&(py->sommets), p);
};

//ajoute un sommet (point) à un polygone
//revoie la taille de la liste après opération
//ou -1 si le point est déjà présent
//ou -2 si la liste est pleine
int add_sommet_polygone(polygone* py, point* p){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(p==NULL){
		perror("error parametre null");
		exit(2);
	}

	return add_point_liste(&(py->sommets), p);
};

//retire un sommet(point) à un polygone
//revoie la taille de la liste après opération
// ou -1 si le point n'est pas présent dans le polygone
int remove_sommet_polygone(polygone* py, point* p){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(p==NULL){
		perror("error parametre null");
		exit(2);
	}

	return remove_point_liste(&(py->sommets), p);
};

//supprime un polygone
void delete_polygone(polygone* py){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	delete_liste_point(&(py->sommets));
};

void afficher_polygone(polygone* py){

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	printf("DEBUT Polygone\n");
	printf("Id = %d\n", py->id);
	printf("Sommets :\n");
	afficher_liste_point(&(py->sommets));
	printf("FIN Polygone\n");
	printf("\n");
};


//---------- LISTE DE POLYGONES ----------

//initialise une liste de polygones
void init_liste_polygone(liste_polygone* l){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	l->liste = (polygone**) malloc(TAILLE_MAX_LISTE_POLYGONE * sizeof(polygone*));
	if(l->liste == NULL){
		perror("error malloc");
		exit(1);
	}

	l->nb_polygone = 0;
}

//teste la présence d'un polygone dans une liste
//renvoie l'index du polygone si il est présent
//-1 sinon
int contient_polygone_liste(liste_polygone* l, polygone* py){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	int i;
	for(int i = 0; i<l->nb_polygone; i++)
		if(l->liste[i]->id==py->id)
			return i;

	return -1;
};


//ajoute un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est déjà présent dans la liste
// ou -2 si la liste est pleine
int add_polygone_liste(liste_polygone* l, polygone* py){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	if (contient_polygone_liste(l, py)!=-1) return -1;

	if(l->nb_polygone+1>TAILLE_MAX_LISTE_POLYGONE) return -2;

	l->liste[l->nb_polygone] = py;
	l->nb_polygone++;

	return l->nb_polygone;
};

//retire un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est n'est pas présent dans la liste
int remove_polygone_liste(liste_polygone* l, polygone* py){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	if(py==NULL){
		perror("error parametre null");
		exit(2);
	}

	int index, i;

	index = contient_polygone_liste(l, py);
	if (index == -1) return -1;

	for(i = index; i<(l->nb_polygone)-1; i++)
		l->liste[i] = l->liste[i+1];

	l->nb_polygone--;

	return l->nb_polygone;
};

//supprime une liste de polygone et libère sa composante liste
void delete_liste_polygone(liste_polygone* l){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	free(l->liste);
};

void afficher_liste_polygone(liste_polygone* l){

	if(l==NULL){
		perror("error parametre null");
		exit(2);
	}

	int i, n = l->nb_polygone;

	printf("DEBUT Liste de polygones\n");
	printf("Nb éléments : %d\n", n);

	if(n==0){printf("liste vide\n");}
	else{
        for(i=0; i<n; i++){
            printf("Index : %d\n", i);
            afficher_polygone((l->liste[i]));
            printf("\n");
        }
	}

	printf("FIN Liste de polygones\n");
	printf("\n");
}





