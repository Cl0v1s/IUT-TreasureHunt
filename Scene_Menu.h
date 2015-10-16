#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Lib.h"
#include "Map.h"
#include "Constantes.h"
#include "Button.h"
#include "Player.h"


int menu(SDL_Surface *screen);

int manageInputMenu(Button *play, Button *scores, Button *quit);

void drawMenu(SDL_Surface *screen, TTF_Font * h1, Button *play,Button *scores, Button *quit);

#endif // SCENE_MENU_H
