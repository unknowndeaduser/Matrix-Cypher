#include <stdio.h>
#include <stdlib.h>
#include "tic.h"

void initialiserTic(tic *t)
{

    //Charger les 3 images 
    t->boxes = SDL_LoadBMP("fond.bmp"); // IMG_Load ( si lo format .png ou autre )
    t->xs = SDL_LoadBMP("xs.bmp");
    t->os = SDL_LoadBMP("os.bmp");
    //Initialiser les case de tableau a 0 
    int i;
    for (i = 0; i < 9; i++)
        t->tabsuivi[i] = 0;

    t->pos.x = 0 ; 
    t->pos.y = 0 ;
     
    t->joueur = 1;
    t->tour = 0;
    t->font = TTF_OpenFont("comic.ttf", 40);
    t->couleur.r = 0;
    t->couleur.g = 0;
    t->couleur.b = 0;
    t->postxt.x = 0;
    t->postxt.y = 0;
}

void afficherTic(tic t, SDL_Surface *ecran)
{
    int i;
    SDL_BlitSurface(t.boxes, NULL, ecran, NULL);
    for (i = 0; i < 9; i++)
    {
        t.pos.x = 190 * (i % 3);
        t.pos.y = 190 * (i / 3);
        switch (t.tabsuivi[i])
        {
        case -1:
            SDL_BlitSurface(t.xs, NULL, ecran, &t.pos);
            break;
        case 1:
            SDL_BlitSurface(t.os, NULL, ecran, &t.pos);
            break;
        }
    }
}

void Resultat(tic t, SDL_Surface *ecran)
{
    SDL_Rect pos;
    char msg[20];

    pos.x = 0;
    pos.y = 0;
    afficherTic(t, ecran);
    switch (atilganer(t.tabsuivi))
    {
    case 0:
        strcpy(msg, "NULL");
        break;
    case 1:
        strcpy(msg, "you lost");
        break;
    case -1:
        strcpy(msg, "you win");
    }

    SDL_BlitSurface(TTF_RenderText_Solid(t.font, msg, t.couleur), NULL, ecran, &t.postxt);
    SDL_Flip(ecran);
    SDL_Delay(4000);
}

void liberationmemoire(tic t)
{
    SDL_FreeSurface(t.boxes);
    SDL_FreeSurface(t.xs);
    SDL_FreeSurface(t.os);
}

int atilganer(int tabsuivi[])
{
    // remplir cette matrice avec les combinaisons de succÃ©s
    int lignes_gagnantes[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    //  0, 1, 2
    //  3, 4, 5
    //  6, 7, 8
    //  0, 3, 6
    //
    //
    //
    //

    int i;
    for (i = 0; i < 8; ++i)
        if (tabsuivi[lignes_gagnantes[i][0]] != 0 &&
            tabsuivi[lignes_gagnantes[i][0]] == tabsuivi[lignes_gagnantes[i][1]] &&
            tabsuivi[lignes_gagnantes[i][0]] == tabsuivi[lignes_gagnantes[i][2]])
            return tabsuivi[lignes_gagnantes[i][2]];
    return 0;
}

int minimax(int tabsuivi[], int joueur)
{
    int gagnant = atilganer(tabsuivi);
    if (gagnant != 0)
        return gagnant * joueur;
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; ++i)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = joueur;
            int mmscore = -minimax(tabsuivi, joueur * -1);
            if (mmscore > score)
            {
                score = mmscore;
                coup = i;
            }
            tabsuivi[i] = 0;
        }
    }
    if (coup == -1)
        return 0;
    return score;
}

void calcul_coup(int tabsuivi[])
{
    int coup = -1;
    int score = -2;
    int i;
    for (i = 0; i < 9; ++i)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = 1;
            int mmscore = -minimax(tabsuivi, -1);
            tabsuivi[i] = 0;
            if (mmscore > score)
            {
                score = mmscore;
                coup = i;
            }
        }
    }
    tabsuivi[coup] = 1;
}



int Tic (){
//Init SDL 
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    //t:tic
    tic t ; 
    //ecran:SDL_Surface 
    SDL_Surface *ecran ; 
    ecran = SDL_SetVideoMode(552,541, 32,SDL_HWSURFACE| SDL_DOUBLEBUF); 

    int continuer = 1 ; 
    int x , y  ; 
    int coup ; 
    
    int result = -2;

    initialiserTic(&t);

    SDL_Event event;

    while (continuer)
    {
        afficherTic(t,ecran);

        if( t.tour<9 &&atilganer(t.tabsuivi)==0)
        {
            if((t.tour+t.joueur)%2==0)//tour du PC
                    {calcul_coup(t.tabsuivi);
                    t.tour++;}
                else
                {
                SDL_WaitEvent(&event);
                switch(event.type)
                {
                case SDL_QUIT:
                    continuer=0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    x=event.button.x/190;
                    y=event.button.y/190;
                    coup=3*y+x;
                    t.tabsuivi[coup]=-1;
                    t.tour++;
                    break;
                }

           // t.tabsuivi[t.tour]=-1;
        }

        }
        else
        { Resultat(t,ecran);
        continuer=0;   
        result = atilganer(t.tabsuivi);
        }
        SDL_Flip(ecran);
    }   
   SDL_Quit();
   TTF_Quit();
    liberationmemoire(t);


    
    



    return result;
} 




