#include "entite.h"

int 
	nb_frame=12 ,
	entite_h=195,
	entite_w=135,
	entite_y=0,
	pos_init_x=700,
	pos_init_y=300,
	entite_x=0;



void init_tab_anim_entite(SDL_Rect *clip,entite *e)
{	
	for (int j=0;j<nb_frame; j++)
	{
		clip[j].h=entite_h;
		clip[j].w=entite_w;
		clip[j].x = j*entite_w;
		clip[j].y = 0;
        }  
}

void initialiser_entite(entite *e)
{
	e->entite = IMG_Load("ES4.png");
	e->pos_entite.x = pos_init_x;
	e->pos_entite.y = pos_init_y;
	init_tab_anim_entite(e->anim_entite,e);
	e->frame_entite=0;
	e->direction=0;  
	
}


void afficher_entite(entite * e , SDL_Surface *screen)
{
	SDL_BlitSurface(e->entite,&e->anim_entite[e->frame_entite], screen, &e->pos_entite);
}


void mvt_entite(entite *e,personnage *p)
{
	int diff_x=e->pos_entite.x-p->perso_pos.x;	
  	int diff_y=p->perso_pos.y-e->pos_entite.y;
	if (diff_x<350 && diff_x>50 )
	{
		e->pos_entite.x-=3;

		if(diff_y<350 && diff_y>50)
	{
		e->pos_entite.y+=3;
	}
	else if (diff_y >350)
	{
		e->pos_entite.y = pos_init_y;
	}


		if (diff_y >-350 && diff_y < 0 )
	{
		e->pos_entite.y-=3;
	} 

	else if (diff_y < -350)
	{
		e->pos_entite.y = pos_init_y;
	}


  	}
	else if (diff_x > 350 )
	{
		e->pos_entite.x = pos_init_x;
	}

	if (diff_x >-350 && diff_x < 0)
	{
  		e->pos_entite.x+=3;

		if(diff_y<350 && diff_y>50)
	{
		e->pos_entite.y+=3;
	}
	else if (diff_y >350)
	{
		e->pos_entite.y = pos_init_y;
	}


		if (diff_y >-350 && diff_y < 0 )
	{
		e->pos_entite.y-=3;
	} 

	else if (diff_y < -350)
	{
		e->pos_entite.y = pos_init_y;
	}

  	}
	else if (diff_x <-350 )
	{
		e->pos_entite.x = pos_init_x;
	}
	
	
	
	

}


void anim(entite *e)
{   
	if (e->frame_entite >=0 && e->frame_entite <(nb_frame-1)) {
 		e->frame_entite++;
		}
	if ( e->frame_entite ==(nb_frame-1)) {
		e->frame_entite=0;
		}
}


void update_entite(entite *e,personnage *p)
{	
	if (e->pos_entite.x!=0&&e->pos_entite.y!=0)
	{ 	
		mvt_entite(e,p);
		anim(e);
	}	
}



int detect_collision(personnage *p, entite* e)
{
    // Calculate the ranges for both x and y coordinates for person and enemy
    int person_left = p->perso_pos.x;
    int person_right = p->perso_pos.x + p->perso_pos.w;
    int person_top = p->perso_pos.y;
    int person_bottom = p->perso_pos.y + p->perso_pos.h;

    int enemy_left = e->pos_entite.x;
    int enemy_right = e->pos_entite.x + e->pos_entite.w;
    int enemy_top = e->pos_entite.y;
    int enemy_bottom = e->pos_entite.y + e->pos_entite.h;

    // Check for intersection in both x and y coordinates
    if (person_right >= enemy_left && person_left <= enemy_right && 
        person_bottom >= enemy_top && person_top <= enemy_bottom)
    {
        return 1; // Collision detected
    }
    else
    {
        return 0; // No collision
    }
}



int gestion(entite* e)
{ 	
	return 0;
}




void initialiser_perso(personnage *p)
{
	p->perso= IMG_Load("perso1.png");
	p->perso_pos.x = 104.7;
	p->perso_pos.y = 393;
	p->perso_pos.h = 281;
	p->perso_pos.w = 217;  
}

void afficher_perso(personnage * p , SDL_Surface *screen)
{
	SDL_BlitSurface(p->perso,NULL, screen, &p->perso_pos);
}
void initennemi(enemie*e) {
    e->spritesheet=IMG_Load("ennemi.png");
    e->frame=0;
    e->direction=1; 
    e->pos.x=1246.7;
    e->pos.y=616.8;
    e->posframe.x=0;
    e->posframe.y=0;
    e->posframe.h=100;
    e->posframe.w=100;
    e->posmax.x=2200;
    e->posmin.x=1900;

}


void afficherennemi(enemie *e, SDL_Surface * screen) {
   if (e->pos.x>0) SDL_BlitSurface(e->spritesheet,&e->posframe,screen,&e->pos);
}

void animerennemi( enemie * e) {
    e->posframe.y = e->direction * 100 ;		
    e->posframe.x = e->posframe.x + 100;
    if (e->posframe.x==400)
    {
        e->posframe.x=0;
    }
    
} 


void deplacer(enemie *e) {
    if (e->direction == 0) {
        e->pos.x -= 5; // Move left
    } else if (e->direction == 1) {
        e->pos.x += 5; // Move right
    }

    if (e->pos.x > e->posmax.x) {
        e->direction = 1; // bot yemshy imin
    }
    if (e->pos.x < e->posmin.x) {
        e->direction = 0; // bot yemshi isar
    }
}

int collision(SDL_Rect E, SDL_Rect p) {
  int collision,px,py;
  px=p.x+100;
  py=p.y+120;
  if (((px + p.w) < E.x) || (px > (E.x + E.w)) || ((py + p.h) < E.y) || (py > (E.y + E.h))) {
    collision = 0;
  } else {
    collision = 1;
  }

  return collision;
}


void deplacerIA(enemie * E, SDL_Rect posPerso) {
  if (((E -> pos.x - posPerso.x) < 200) && ((E -> pos.x - posPerso.x) > 80))  
   {
    E -> direction = 1; 
    E -> pos.x -= 8;
  } 
  else if (((E -> pos.x - posPerso.x) < -80) && ((E -> pos.x - posPerso.x) > -400))
   {
    E -> direction = 0; 
    E -> pos.x += 8;
  } 
  else if (((E -> pos.x - posPerso.x) <= 80) && ((E -> pos.x - posPerso.x) >= 0)) 
  {
    E -> direction = 3;
  } 
  else if (((E -> pos.x - posPerso.x) <= 0) && ((E -> pos.x - posPerso.x) >= -80)) 
  {
    E -> direction = 2;
  }
  else deplacer(E);

}

void scrolling_enemie(enemie *E,int direction,int pasAvancement){
  if (direction==1)
	{
		 E->pos.x += pasAvancement;
     E->posmin.x += pasAvancement;
     E->posmax.x += pasAvancement;
	}else if (direction==0)
	{
		E->pos.x -= pasAvancement;
    E->posmin.x -= pasAvancement;
    E->posmax.x -= pasAvancement;
	}
}
