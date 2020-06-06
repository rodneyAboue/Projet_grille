#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WINDOW_WIDHT 1280
#define WINDOW_HEIGHT 720
#define NUMMENU 5
//TYPES
typedef enum bool
{
	false,
	true,
}bool;

typedef enum
{
	image_shom,
	affichage_polygone,
	ajout_point,
	ajout_ligne,
	quitter,
	null,
	ajout_premier_point_ligne,
	ajout_deuxieme_point_ligne,
}clickedStep;

typedef struct $
{
	int red;
	int green;
	int blue;
}myColor;


/*-------------------------------*/
/*--FUNCTIONS--------------------*/
	bool load_shom_image(char name []);
	bool load_fond();
	bool load_menu();
	void clean_all( SDL_Window *w, SDL_Renderer *r, SDL_Texture *t,SDL_Texture *t2);
	int button_cliked();
	bool dessine_graphique_point(int x, int y, myColor couleur);
	int in_frame(int x, int y);
	//dessine_graphique_point2 ne marche pas
	bool dessine_graphique_point2(myColor couleur);
	bool dessine_graphique_ligne(int x1, int y1 ,int x2, int y2, myColor couleur);
/*-------------------------------*/

	SDL_Window *window = NULL;
	SDL_Renderer *renderer= NULL;
	SDL_Surface *picture = NULL;
	SDL_Surface *surfaceMenu=NULL; 
	SDL_Texture *texture = NULL;
	SDL_Texture *textureMenu = NULL;
	SDL_Rect dest = { 0, 0, WINDOW_WIDHT, WINDOW_HEIGHT};
	SDL_Rect cadre = { 215, 90, 1064, 629};  
	TTF_Font  *menuFont; 
	SDL_Color fontBlack ={250,250,250};
	const char menutexte[NUMMENU][20] = {"Affichage image","Affichage polygone","Ajout point", "Ajout ligne","Quitter"};
	myColor red={255,0,0};
	myColor green={0,255,0};
	myColor blue={0,0,255};
	myColor white ={255,255,255};
	myColor black ={0,0,0,};
int main(int argc, char *argv[])
{
	//variables 

	// sdl version
	SDL_version nb;
	SDL_VERSION (&nb);
	printf("Programme test grille\n");
	printf("SDL: %d.%d.%d\n",nb.major, nb.minor ,nb.patch );
	
	// SDL init 
	if(SDL_Init(SDL_INIT_VIDEO)!=0)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(NULL,NULL,NULL,NULL);
		exit(EXIT_FAILURE);
	}

	// creation de la fenetre 
	window=SDL_CreateWindow("grille",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDHT,WINDOW_HEIGHT,0);
	if(window==NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(NULL,NULL,NULL,NULL);
		exit(EXIT_FAILURE);
	}
	
	//creation du rendu 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer==NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,NULL,NULL,NULL);
		exit(EXIT_FAILURE);
	}

	if(TTF_Init()!=0)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,renderer,texture,NULL);
		exit(EXIT_FAILURE);
	}
	menuFont= TTF_OpenFont("raleway/Raleway-Regular.ttf",20);
	if (menuFont==NULL)
	{
		SDL_Log("Erreur : > %s \n" , TTF_GetError());
		clean_all(window,renderer,texture,NULL);
		exit(EXIT_FAILURE);
	}
	
	//printf("ok1\n");

	
	clickedStep clicked_state = null;
	if (load_fond()==true && load_menu()== true)
	{
		//loading
	}
	else
	{
		clean_all(window,renderer,texture,textureMenu);
		exit(EXIT_FAILURE);
	}
	SDL_bool running = SDL_TRUE;
	int choice=0;
	clickedStep choice_before=null;
	while(running)
	{
		SDL_Event event;
		
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEMOTION:
					//printf("<%d %d>\n",event.motion.x, event.motion.y );
					break;
				case SDL_MOUSEBUTTONDOWN:
					
					choice=button_cliked(event.button.x, event.button.y);
					printf("Le boutton %d a ete cliqué\n", choice);
					printf("choice before %d\n",choice_before );
					switch(choice)
					{
						case 1:
							if(load_shom_image("img/shom.png")==false)
							{
								clean_all(window,renderer,texture,textureMenu);
								exit(EXIT_FAILURE);
							}
							clicked_state=image_shom;
							choice_before=clicked_state;
						break;
					
						case 2:
							if (load_fond()==true && load_menu()== true)
							{
								//loading
							}
							else
							{
								clean_all(window,renderer,texture,textureMenu);
								exit(EXIT_FAILURE);		
							}
							//printf("voir suite\n");
							clicked_state=affichage_polygone;
							choice_before=clicked_state;
						break;

						case 3:
							if (clicked_state==image_shom)
							{
								if (load_fond()==true && load_menu()== true)
								{
									//loading
								}
								else
								{
									clean_all(window,renderer,texture,textureMenu);
									exit(EXIT_FAILURE);		
								}
								//printf("voir suite\n");
								
								clicked_state=ajout_point;
								choice_before=clicked_state;
								printf("je suis dan ajout point:state %d  before %d \n",clicked_state,choice_before );
							}

						break;

						case 4:
							if (clicked_state==image_shom)
							{
								if (load_fond()==true && load_menu()== true)
								{
									//loading
								}
								else
								{
									clean_all(window,renderer,texture,textureMenu);
									exit(EXIT_FAILURE);		
								}
								//printf("voir suite\n");
								
								clicked_state=ajout_ligne;
								choice_before=clicked_state;
								printf("state %d  before %d \n",clicked_state,choice_before );
							}
						break;

						case 5:
							clicked_state=quitter;
							choice_before=clicked_state;
							running =SDL_FALSE;
						break;

						case 6:
							//printf("state %d  before %d \n",clicked_state,choice_before );
							if (choice_before==5)
							{
								printf("ok\n");
								if(dessine_graphique_point(event.button.x, event.button.y,red)==true)
								{
									printf("le point a ete dessine\n");
								}	
								else
								{
									clean_all(window,renderer,texture,textureMenu);
									exit(EXIT_FAILURE);	
								}
								choice_before=null;
							}
							/*if (choice_before==ajout_ligne)
							{
								if(dessine_graphique_point(event.button.x, event.button.y,red)==true)
								{
									printf("le point a ete dessine\n");
								}	
								else
								{
									clean_all(window,renderer,texture,textureMenu);
									exit(EXIT_FAILURE);	
								}
								choice_before=null;
							}*/
						break;

						default:
						break;
					}
					  
					break;
				case SDL_QUIT :
					running =SDL_FALSE;
				break;
				
				default:
				break;
			}
		}
		SDL_RenderPresent(renderer);
	}
	
	// fin du programme
	//destruction de la fenetre
	clean_all(window,renderer,texture,textureMenu);	
	return 0;
}
/*-----------------------------------------------------------------------------*/
void clean_all( SDL_Window *w, SDL_Renderer *r, SDL_Texture *t,SDL_Texture *t2)
{
	if (w != NULL)
		SDL_DestroyWindow(w);
	
	if (r != NULL)
		SDL_DestroyRenderer(r);	

	if (t != NULL)
		SDL_DestroyTexture(t);
	if (t2 != NULL)
		SDL_DestroyTexture(t2);

	SDL_Quit();
	TTF_CloseFont(menuFont);
	TTF_Quit();
}
/*-----------------------------------------------------------*/
bool load_shom_image( char name [])
{
	picture = IMG_Load(name);
	if (picture == NULL)
	{
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL)
	{
		return false;
	}

	if (SDL_QueryTexture(texture, NULL,NULL,&cadre.w, &cadre.h) !=0)
	{
		return false;
	}

	cadre.x = ((WINDOW_WIDHT - cadre.w)/2)+10;
	cadre.y = (WINDOW_HEIGHT -cadre.h)/2;
	if (SDL_RenderCopy(renderer,texture,NULL ,&cadre) !=0)
	{
		return false;
	}

	return true;
}

/*-----------------------------------------------------------*/
bool load_fond()
{
	picture = IMG_Load("img/Black.jpg");
	if (picture == NULL)
	{
		return false;
	}

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL)
	{
		return false;
	}

	if (SDL_QueryTexture(texture, NULL,NULL,&dest.w, &dest.h) !=0)
	{
		return false;
	}

	dest.x = (WINDOW_WIDHT - dest.w)/2;
	dest.y = (WINDOW_HEIGHT -dest.h)/2;
	if (SDL_RenderCopy(renderer,texture,NULL ,&dest) !=0)
	{
		return false;
	}
	return true;
}
bool load_menu()
{
	for (int i = 0; i < NUMMENU; ++i)
	{
		char texte[20];
		strcpy(texte,menutexte[i]);
		surfaceMenu=TTF_RenderText_Blended(menuFont,texte, fontBlack);
		textureMenu = SDL_CreateTextureFromSurface(renderer, surfaceMenu);
		if (textureMenu == NULL)
		{
			return false;
		}
		SDL_FreeSurface(surfaceMenu);
		SDL_Rect destMenu;
		destMenu.x=30;
		destMenu.y=100+(i*40); 
		if (SDL_QueryTexture(textureMenu, NULL,NULL,&destMenu.w, &destMenu.h) !=0)
		{
			return false;
		}

		if (SDL_RenderCopy(renderer,textureMenu,NULL ,&destMenu) !=0)
		{
			return false;
		}
	}
	return true;
}
/*-----------------------------------------------------------*/
int button_cliked(int x, int y)
{
	printf("<%d ,%d>\n",x,y );
	if (x>=30 && x<=184 && y>=100 && y<=120)
	{
		// boutton afficher image 
		return 1;
	}                        
	if (x>=30 && x<=213 && y>=142 && y<=160)
	{
		// boutton afficher polygone 
		return 2;
	}
	if (x>=30 && x<=130 && y>=182 && y<=197)
	{
		// boutton ajouter point 
		return 3;
	}
	if (x>=30 && x<=130 && y>=224 && y<=240)
	{
		// boutton ajouter ligne 
		return 4;
	}
	if (x>=30 && x<=92 && y>=262 && y<=279)
	{
		// boutton quitter
		return 5;
	}

	if (x>=215 && x<=1064 && y>=90 && y<=629)
	{
		// boutton dans le cadre 
		return 6;
	}
	return -1;
}

/*-----------------------------------------------------------*/
bool dessine_graphique_point(int x, int y, myColor couleur)
{
	if (SDL_SetRenderDrawColor(renderer, couleur.red, couleur.green, couleur.blue, SDL_ALPHA_OPAQUE)!=0)
	{
		return false;
	}	
	SDL_Rect carre = { x, y, 4, 4};
	if (SDL_RenderFillRect(renderer,&carre)!=0)
	{
		return false;
	}
	return true;
}

/*---------------------------------------------------------------*/
bool dessine_graphique_ligne(int x1, int y1 ,int x2, int y2, myColor couleur)
{
	if (SDL_SetRenderDrawColor(renderer, couleur.red, couleur.green, couleur.blue, SDL_ALPHA_OPAQUE)!=0)
	{
		return false;
	}	
	
	if (SDL_RenderDrawLine(renderer,x1,y1,x2,y2)!=0)
	{
		return false;
	}
	return true;
}