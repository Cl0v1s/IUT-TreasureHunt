#ifndef SCENE_WIN_H
#define SCENE_WIN_H


#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include "Constantes.h"
#include "Lib.h"
#include "Button.h"
#include "Player.h"


int win(SDL_Surface *screen, Player *winner);

int manageInputWin(Button *replay, Button *quit);

int readBestScore();

void saveScore(int score);

void readAllScores(int score[], int &nb_score);

#endif // SCENE_WIN_H
