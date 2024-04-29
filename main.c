
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <time.h>
#include "entite.h"


	int main()
	{
	
	int a=1;
	int b=0;
	int done=1;
	
	SDL_Init(SDL_INIT_VIDEO);

//creation de la fenetre 
	SDL_Surface *screen;
	 	if(SDL_Init(SDL_INIT_VIDEO)!=0)
		{
			printf("unable to initialize SDL: %s\n",SDL_GetError());
			return 1;
		}	
 			screen=SDL_SetVideoMode(1360,765,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		if(screen==NULL)
		{
			printf("unable to set video mode:%s\n",SDL_GetError());
			return 1;
		}
			SDL_WM_SetCaption("ENTITE SECONDAIRE ", NULL); 

// creation background
	SDL_Surface *background ;
	SDL_Rect background_pos;
	background = IMG_Load("back.png");
	background_pos.x = 0;
	background_pos.y = 0;


 
//init entite

	entite e;
	initialiser_entite (&e) ;

//init personnage 
	enemie enemy;
        initennemi(&enemy);
//init enemie

	personnage p;
	initialiser_perso (&p) ;
	SDL_EnableKeyRepeat(200, 0);
	SDL_Event event;

        while (done)
	{ 	 SDL_BlitSurface(background,NULL,screen,&background_pos);
		afficher_perso(&p ,screen);
		afficherennemi(&enemy, screen);
		
		SDL_PollEvent(&event);

                        switch (event.type) 
                        {

                        case SDL_QUIT: 
                                done = 0;
                                break;

                        case SDL_KEYDOWN:                     
                                switch (event.key.keysym.sym) 
                                {
                                case SDLK_RIGHT: 
                                         
                                      p.perso_pos.x += 10;

                                        break;

                                case SDLK_LEFT: 
                                        p.perso_pos.x -= 10;
                                     
                                         
                                        break;
                                case SDLK_UP: 
                                        p.perso_pos.y -= 10;
                                        break;

                                case SDLK_DOWN: 
                                      p.perso_pos.y += 10;
                                        break;
                                }
                        } //fin switch



	update_entite(&e,&p);
	b = collision(enemy.pos, p.perso_pos);
	
	
	b=detect_collision(&p,&e);
 	if(b) a=gestion(&e);
	if (a){ afficher_entite(&e ,screen);}
        animerennemi(&enemy);
        deplacerIA(&enemy, p.perso_pos);
	
	
	//SDL_Delay(10);
	SDL_Flip(screen);

	}

	SDL_FreeSurface(background);
	SDL_Quit();

    return 0;
}
