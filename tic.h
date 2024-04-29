#ifndef ENTETE_H_INCLUDED
#define ENTETE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


// La Structure Tic
typedef struct
{

    SDL_Surface * boxes; // Background Grille 
    SDL_Surface *xs,*os;    // Image X et O 
    
    int tabsuivi[9]; 

    SDL_Rect pos;

    int joueur;

    int tour;

    TTF_Font *font;
    SDL_Color couleur;
    SDL_Rect postxt;
}tic;
//
void initialiserTic(tic *t);

void afficherTic(tic t,SDL_Surface *ecran ) ;

int atilganer(int tabsuivi[]);

int minimax(int tabsuivi[],int joueur);

void calcul_coup(int tabsuivi[]);

void Resultat (tic t,SDL_Surface* ecran);

void liberationmemoire(tic t);

int Tic();

#endif // ENTETE_H_INCLUDED
