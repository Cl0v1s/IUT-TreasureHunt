#ifndef MAP_H
#define MAP_H

#include <SDL/SDL.h>
#include <iostream>
#include <cstdlib>
#include "Constantes.h"
#include "Lib.h"

/* *********************** Nom de la structure ************************
* Coin
*************************** Auteur, Dates ****************************
* C. Portron, 20/11/14
*************************** Description ******************************
* Pièce
*************************** valeurs **********************************
* value, valeur de la pièce
**********************************************************************/
typedef struct
{
    int value;
}Coin;

typedef Coin Map[MAP_SIZE][MAP_SIZE];



void initMap(Map _map);

void generatePossibilities(int pos[], int &length);

void removePossibility(int m[], int &length, int index);

int getIndexInSpriteSheet(int value);

void drawMap(Map _map, SDL_Surface *coins, SDL_Surface *screen);

#endif
