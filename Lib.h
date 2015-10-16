#ifndef Lib_H
#define Lib_H

#include <stdlib.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <sstream>
#include <iostream>
#include <math.h>

#include "Constantes.h"

/* *********************** Nom de la structure ************************
* Rectangle
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* rectangle formé par des nombres réels
*************************** valeurs **********************************
* x, position x du rectangle
* y, position y du retangle
* width, largeur du rectangle
* height, hauteur du rectangle
**********************************************************************/
struct Rectangle
{
    float x;
    float y;
    float width;
    float height;
};

/* *********************** Nom de la structure ************************
* Vector2
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Vecteur (ou ensemble de duex coordonées)
*************************** valeurs **********************************
* x, position x du vecteur
* y, position y du vecteur
**********************************************************************/
struct Vector2
{
    float x;
    float y;
};

/* *********************** Nom de la structure ************************
* RGBA
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* couleur possédant un canal alpha
*************************** valeurs **********************************
* r, quantité de rouge
* g, quantité de vert
* b, quantité de bleu
* a, opacité (min: 0, max: 255)
**********************************************************************/
struct RGBA
{
    int r;
    int g;
    int b;
    int a;
};




//Charge une image
SDL_Surface *load_image(std::string filename);

//Charge une image avec la transparence
SDL_Surface *LoadImageTransparent(std::string filename, int r, int g , int b);

//Colle une image à l'écran
void applySurface(int x,int y,SDL_Surface *toapply, SDL_Surface *onapply, SDL_Rect* clip );

//affiche du texte à l'écran
void drawText(std::string message,int x,int y,TTF_Font *font,int fontSize,RGBA textColor,SDL_Surface* &screen);

Vector2 getTextSize(std::string text, TTF_Font *font);

int randInt(int mi, int ma);

void manageFrames(int startMs);

std::string convertToString(int e);

void moveIntArrayRight(int tab[], int index, int &length, int max_length);
#endif
