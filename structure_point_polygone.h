//-------------------- STRUCTURE DE DONNEES --------------------

//---------- POINTS ----------

//int id_point = 1;

typedef struct st_liste_point liste_point;
typedef struct st_point point;

struct st_liste_point{
	point** liste;
	int nb_point;
};

struct st_point{
	int id;
	float x;
	float y;
	char etat;

	liste_point voisins;
};


//---------- POLYOGNES ----------

//int id_polygone = 1;

typedef struct st_polygone{
	int id;
	
	liste_point sommets;

	char etat;
	
} polygone;


typedef struct st_liste_polygones{
	polygone** liste;
	int nb_polygone;
} liste_polygone;


//-------------------- FONCTIONS ASSOCIEES --------------------

//---------- POINTS ----------

void init_point(point* p);
//initialise un point 
//lui donne un id unique et alloue la liste des voisins
//renvoie le pointeur passé en paramètre 

void delete_point(point* p);
//supprime un point

void afficher_point(point *p);
//affiche un point



//---------- LISTE DE POINTS ----------

void init_liste_point(liste_point* l);
//initialise une liste de points
//alloue sa composante liste
//renvoie le pointeur passé en paramètre

int contient_point_liste(liste_point* l, point* p); 
// renvoie l'index du point
// renvoie -1 si le point n'est pas trouve

int add_point_liste(liste_point* l, point* v);
//ajoute un point à une liste de points
//revoie l'id du point ajouté 
// ou -1 si le point est déjà présent dans la liste
// ou -2 si la liste est pleine

int remove_point_liste(liste_point* l, point* v);
//retire un point à une liste de points
//revoie l'id du point retiré 
// ou -1 si le point n'est pas présent dans la liste

void delete_liste_point(liste_point* l);
//supprime une liste de points et libère sa composante liste

void afficher_liste_point(liste_point* l);
//affiche une liste de points




//---------- POLYGONE ----------

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
void init_liste_polygone(liste_polygone* l);

//teste la présence d'un polygone dans une liste
//renvoie l'index du polygone si il est présent
//-1 sinon
int contient_polygone_liste(liste_polygone* l, polygone* py);


//ajoute un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est déjà présent dans la liste
// ou -2 si la liste est pleine
int add_polygone_liste(liste_polygone* l, polygone* py);

//retire un polygone à une liste de polygones
//revoie la taille de la liste après opération
// ou -1 si le polygone est n'est pas présent dans la liste
int remove_polygone_liste(liste_polygone* l, polygone* py);

//supprime une liste de polygone et libère sa composante liste
void delete_liste_polygone(liste_polygone* l);

//affiche une liste de polygones sous la forme : 
//DEBUT Liste de polygones 
//Nb éléments : x
// Index : 1
//*Affichage du polygone*



//
//Index : 2
//etc...
//FIN Liste de polygone
void afficher_liste_polygone(liste_polygone* l);
