#ifndef SCENE_SCORES_H
#define SCENE_SCORES_H

#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Lib.h"
#include "Button.h"

int scores(SDL_Surface *screen);

int manageInputScores(Button *ret);

void readScores(int score[], int &nb_score);

void drawScores(int score[], int nb_score, TTF_Font *font, SDL_Surface *screen);

#endif // SCENE_SCORES_H
