#ifndef JAUGE_H
#define JAUGE_H

#include <SDL/SDL.h>
#include <iostream>
#include "Player.h"
#include "Lib.h"


/* *********************** Nom de la structure ************************
* Jauge
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* jauge contenant les informations sur les bonus d'un des joueurs
*************************** valeurs **********************************
* x, position x du buoton
* y, position y du bouton
* progress, vecteur à appliquer au niveau de la jauge pour la faire varier
* level, rectangle contenant le niveau courant de la jauge
* frame, index dans la spritesheet
* player, joueur associé à la jauge
* lastCombo, dernier combo calculé par la jauge
* sprite, spritesheet de la jauge
**********************************************************************/
struct Jauge
{
    int x;
    int y;
    Vector2 progress;
    Rectangle level;
    float frame;
    Player *player;
    int lastCombo;
    SDL_Surface *sprite;
};

Jauge createJauge(int x, int y, Player *player, SDL_Surface *sprite);

void updateJauge(Jauge &jauge);

void resetJauge(Jauge &jauge);

void drawJauge(Jauge jauge, TTF_Font *font,  SDL_Surface *screen);



#endif // JAUGE_H
