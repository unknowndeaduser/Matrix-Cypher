#ifndef entite_H_INCLUDED
#define entite_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<time.h>
typedef struct enemie
	{ 
            SDL_Surface *spritesheet;  
            SDL_Rect pos,posframe;
            int direction; 
            SDL_Rect posmin,posmax;
            int frame; 
     }enemie;

typedef struct 
{
	SDL_Surface *entite ;
	SDL_Rect pos_entite;
	SDL_Rect anim_entite[70];
	int frame_entite;
	int direction;
	int maxi_up,maxi_down;
	
}entite ;

typedef struct
{
	SDL_Surface *perso; 
	SDL_Rect perso_pos ;
}personnage;
	//bonus(6)
	void init_tab_anim_entite(SDL_Rect* clip,entite *e); 
	void initialiser_entite (entite *e) ;
	void afficher_entite(entite * e , SDL_Surface *screen);
	void anim(entite *e);
	void mvt_entite(entite *e,personnage *p);
	void update_entite(entite *e,personnage *p);
        //ena(4)
	void initialiser_perso(personnage *p);
	void afficher_perso(personnage * p , SDL_Surface *screen);
	int detect_collision(personnage *p, entite* e);
	int gestion(entite* e);
	//enemie(5)
	void initennemi(enemie*e)  ;
	void afficherennemi(enemie *e, SDL_Surface * screen) ;
	void animerennemi( enemie * e)  ;   
	void deplacer( enemie * e)  ;  
	int collision(SDL_Rect E, SDL_Rect p);
	void deplacerIA(enemie * E, SDL_Rect posPerso);
	void scrolling_enemie(enemie *E,int direction,int pasAvancement);


#endif 
