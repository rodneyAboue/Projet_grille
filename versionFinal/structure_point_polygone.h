#ifndef STRUCTURES_POINT_POLYGONE
#define STRUCTURES_POINT_POLYGONE

//-------------------- STRUCTURE DE DONNEES --------------------

//---------- POINTS ----------

typedef struct st_point pointp;
typedef struct st_liste_polygone liste_polygone;

typedef struct st_point{
	int id;
	double x;
	double y;
	char etat;

	pointp* next;
} pointp;

typedef struct st_liste_polygone{
	pointp* polygone;
	liste_polygone* next;
}liste_polygone;

//-------------------- FONCTIONS ASSOCIEES --------------------

//---------- POLYGONE ----------

liste_polygone* init_liste_polygone();
// initialise une liste de polygone et la retourne


void add_polygone_liste(liste_polygone* liste, pointp* p);
//ajoute un polygone à une liste de polygones

void afficher_liste_polygone(liste_polygone* lp);
//affiche une liste de polygones

void delete_liste_polygone(liste_polygone *lp);
// supprime tous les elements d'une liste de polygones

//-----------------------POINT-------------------------------------

//initialise un sommet 
//lui donne un id 
//renvoie un pointeur vers le point alloué
pointp* init_sommet();

//initialise un point de la grille 
//lui donne un id 
//renvoie un pointeur vers le point alloué
pointp* init_point_liste_points();

//affiche un point sous le format : 
//- id < x,y >\n
void afficher_point(pointp *p);


//compte le nombre de points d'une liste de points et retourne ce nombre
// Il faut appeler compte_point-liste et non l'autre
int count_point_liste(pointp* liste);
int compte_point_liste_2(pointp* liste, int nb_pts);

// renvoie e pointeur du point
// renvoie -1 si le point n'est pas trouve
pointp* search_point_liste_id(pointp* liste, int id); // inutile ?? 

// renvoie l'index du point
// renvoie -1 si le point n'est pas trouve
pointp* search_point_liste_coords(pointp* liste, double x, double y);

//ajoute un point à une liste de points
//revoie l'id du point ajouté 
// ou -1 si le point est déjà présent dans la liste
int add_point_liste(pointp* liste, double x, double y);


//retire un point à une liste de points
//revoie l'id du point retiré 
// ou -1 si le point n'est pas présent dans la liste
int remove_point_liste(pointp* liste, double x, double y);
	
	

//supprime une liste de points et libère sa composante liste
void delete_liste_point(pointp* liste);

//affiche une liste de points
void afficher_liste_point(pointp* liste);

#endif


/*


//initialise un polygone et lui donne un id unique
//renvoie le pointeur passé en paramètre
void init_polygone(polygone* py);

//teste la présence d'un point dans le polygone
//renvoie l'index si il est présent
//-1 sinon
int contient_point_polygone(polygone* py, point*p);

//ajoute un sommet (point) à un polygone
//revoie la taille de la liste après opération
//ou -1 si le point est déjà présent
//ou -2 si la liste est pleine
int add_sommet_polygone(polygone* py, point* p);

//retire un sommet(point) à un polygone
//revoie la taille de la liste après opération
// ou -1 si le point n'est pas présent dans le polygone
int remove_sommet_polygone(polygone* py, point* p);

//supprime un polygone
void delete_polygone(polygone* py);

//affiche un polygone sous la forme
//DEBUT Polygone
//Id : x
//Sommets: 
// *affichage de la liste de points
//FIN Polygone
void afficher_polygone(polygone* py);


//---------- LISTE DE POLYGONES ----------

//initialise une liste de polygones
//renvoie le pointeur passé en paramètre
void init_liste_polygone(liste_polygone* ptr_l);

//compte le nombre d'éléments d'une liste de polygones
//renvoie le nombre de polygones présents dans la liste
int compter_polygone_liste(liste_polygone* ptr_l);

//teste la présence d'un polygone dans une liste
//renvoie l'index du polygone si il est présent
//-1 sinon
int contient_polygone_liste(liste_polygone* ptr_l, polygone* py);


//ajoute un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est déjà présent dans la liste
// ou -2 si la liste est pleine
int add_polygone_liste(liste_polygone* ptr_l, polygone* py);

//retire un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est n'est pas présent dans la liste
int remove_polygone_liste(liste_polygone* ptr_l, polygone* py);

//supprime une liste de polygone et libère sa composante liste
void delete_liste_polygone(liste_polygone* ptr_l);

//affiche une liste de polygones sous la forme : 
//DEBUT Liste de polygones 
//Nb éléments : x
// Index : 1
//*Affichage du polygone*



//
//Index : 2
//etc...
//FIN Liste de polygone
void afficher_liste_polygone(liste_polygone* ptr_l);


*/
