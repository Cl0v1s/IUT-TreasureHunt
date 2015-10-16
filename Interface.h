#ifndef INTERFACE_H
#define INTERFACE_H


#include <SDL/SDL.h>
#include <string>
#include "Jauge.h"
#include "Lib.h"


/* *********************** Nom de la structure ************************
* Interface
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Interface de jeu contenant diverses informations sur les deux joueurs
*************************** valeurs **********************************
* x, position x de l'interface
* y, poisition y de l'interface
* frame, index de frame
* jauge1, jauge contenant les informations sur les bonus du joueur 1
* jauge2, jauge contenant les informations sur les bonus du joueur 2
* player_1, spritesheet du joueur1
* player_2, spritesheet du joueur 2
* background, fond de l'interface
* coins, spritesheet despièces
* bubble, bulle
**********************************************************************/
struct Interface
{
    int x;
    int y;
    float frame;
    Jauge *jauge1;
    Jauge *jauge2;
    SDL_Surface *player_1;
    SDL_Surface *player_2;
    SDL_Surface *background;
    SDL_Surface *coins;
    SDL_Surface *bubble;
};

Interface createInterface(int x, int y, Jauge *jauge1, Jauge *jauge2);

void loadRessourcesInterface(Interface &interface,SDL_Surface *player_1, SDL_Surface *player_2, SDL_Surface *coins, SDL_Surface *bubble, SDL_Surface  *background);

void updateInterface(Interface &interface);

void drawInterface(Interface interface,TTF_Font *font, SDL_Surface *screen, int currentlyPlaying);




#endif
