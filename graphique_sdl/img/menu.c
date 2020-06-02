//http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum bool
{
	false,
	true,
}bool;
	const int NUMMENU = 2;
	const char* labels[NUMMENU] = {"Continue","Exit"};
	bool selected[NUMMENU] = {0,0};
int showmenu(SDL_Surface* screen, TTF_Font* font)
{
	Uint32 time;
	int x, y;

	SDL_Surface* menus[NUMMENU];
	
	SDL_Color color[2] = {{255,255,255},{255,0,0}};

	menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
	menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);
	SDL_Rect pos[NUMMENU];
	pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
	pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;

	SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));

	SDL_Event event;
	while(1)
	{
		time = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					SDL_FreeSurface(menus[0]);
					SDL_FreeSurface(menus[1]);
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							if(!selected[i])
							{
								selected[i] = 1;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
							}
						}
						else
						{
							if(selected[i])
							{
								selected[i] = 0;
								SDL_FreeSurface(menus[i]);
								menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for(int i = 0; i < NUMMENU; i += 1) {
						if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h)
						{
							SDL_FreeSurface(menus[0]);
							SDL_FreeSurface(menus[1]);
							return i;
						}
					}
					break;
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						return 0;
					}
			}
		}
		for(int i = 0; i < NUMMENU; i += 1) {
			SDL_BlitSurface(menus[i],NULL,screen,&pos[i]);
		}
		SDL_Flip(screen);
		if(1000/30 > (SDL_GetTicks()-time))
			SDL_Delay(1000/30 - (SDL_GetTicks()-time));
	}
}



int main()
{
	SDL_Surface *screen, *icon;
	const int width = 640;
	const int height = 480;
	const int FPS = 30;
	screen = SDL_SetVideoMode(width,height,32,SDL_SWSURFACE);
	TTF_Font *font;
	TTF_Init();

	font = TTF_OpenFont("Test.ttf",30);
	SDL_Color color = {0,0,0};
	SDL_Event event;
	Uint32 start;
	bool running = true;
	bool arr[4] = {0,0,0,0};

	int i = showmenu(screen, font);
	if(i==1)
		running = false;
	while(running)
	{
		
	}
	// deinitialization

	Mix_CloseAudio();
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}