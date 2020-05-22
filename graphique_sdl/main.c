#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDHT 1280
#define WINDOW_HEIGHT 720//functions

typedef enum bool
{
	true,
	false
}bool;
/*-------------------------------*/
	bool load_shom_image(char name []);
	bool load_menu();
	void clean_all( SDL_Window *w, SDL_Renderer *r, SDL_Texture *t);
/*-------------------------------*/
	SDL_Window *window = NULL;
	SDL_Renderer *renderer= NULL;
	SDL_Surface *picture = NULL;
	SDL_Texture *texture = NULL;
	SDL_Rect dest = { 0, 0, WINDOW_WIDHT, WINDOW_HEIGHT}; 
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
		clean_all(NULL,NULL,NULL);
		exit(EXIT_FAILURE);
	}
	
	// creation de la fenetre 
	window=SDL_CreateWindow("grille",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDHT,WINDOW_HEIGHT,0);
	if(window==NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(NULL,NULL,NULL);
		exit(EXIT_FAILURE);
	}
	
	//creation du rendu 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (renderer==NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,NULL,NULL);
		exit(EXIT_FAILURE);
	}
	
	picture = IMG_Load("img/Black.jpg");
	if (picture == NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,renderer,NULL);
		exit(EXIT_FAILURE);
	}

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,renderer,NULL);
		exit(EXIT_FAILURE);
	}

	if (SDL_QueryTexture(texture, NULL,NULL,&dest.w, &dest.h) !=0)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,renderer,texture);
		exit(EXIT_FAILURE);
	}

	dest.x = (WINDOW_WIDHT - dest.w)/2;
	dest.y = (WINDOW_HEIGHT -dest.h)/2;
	if (SDL_RenderCopy(renderer,texture,NULL ,&dest) !=0)
	{
		SDL_Log("Erreur : > %s \n" ,SDL_GetError());
		clean_all(window,renderer,texture);
		exit(EXIT_FAILURE);
	}
	/*-----------------------------------------------*/
	/*-----------------------------------------------*/
	if (load_menu()== true)
	{
	 	printf("work!\n");
	}
	else
	{
		printf("Erreur : > Chargement de l'image \n");
		clean_all(window,renderer,texture);
		exit(EXIT_FAILURE);
	}
	bool shom_image_state = false;

	SDL_bool running = SDL_TRUE;
	while(running)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.clicks==2 && shom_image_state == false)
					{
						load_shom_image("img/shom.png");
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
	clean_all(window,renderer,texture);
	return 0;
}

void clean_all( SDL_Window *w, SDL_Renderer *r, SDL_Texture *t)
{
	if (w != NULL)
		SDL_DestroyWindow(w);
	
	if (r != NULL)
		SDL_DestroyRenderer(r);	

	if (t != NULL)
		SDL_DestroyTexture(t);

	SDL_Quit;
}

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
	picture = IMG_Load("img/loadimage.png");
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

	dest.x = 50;
	dest.y = 90;
	if (SDL_RenderCopy(renderer,texture,NULL ,&dest) !=0)
	{
		return false;
	}
	/*--------------------------------------*/
	picture = IMG_Load("img/drawline.png");
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

	dest.x = 50;
	dest.y = 200;
	if (SDL_RenderCopy(renderer,texture,NULL ,&dest) !=0)
	{
		return false;
	}

	return true;
}

