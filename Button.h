#ifndef BUTTON_H
#define BUTTON_H

#include <SDL/SDL.h>
#include "Lib.h"
#include <cstdlib>
#include <string>

/* *********************** Nom de la structure ************************
* Button
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* bouton interractif permettant au jouer d'interragir avec le jeu
*************************** valeurs **********************************
* x, position x du buoton
* y, position y du bouton
* width, largeur du bouton
* height, hauteur du buoton
* sprite, fond du bouton
* font, police utilisée pour le bouton
* text, texte conenu par le bouton
**********************************************************************/
struct Button
{
    int x;
    int y;
    int width;
    int height;
    SDL_Surface *sprite;
    TTF_Font *font;
    std::string text;
};

Button createButton(SDL_Surface *psprite, std::string text, int px, int yp, TTF_Font *font);

void drawButton(Button *pbutton,SDL_Surface *screen);

bool buttonOnClick(SDL_Event *event, Button *button);

#endif // BUTTON
