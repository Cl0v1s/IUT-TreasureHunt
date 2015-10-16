#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include <SDL/SDL.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Lib.h"
#include "Map.h"
#include "Constantes.h"
#include "Button.h"
#include "Player.h"
#include "Jauge.h"
#include "Interface.h"
#include "Scene_Win.h"

//TODO: demander pourquoi ca ne marche pas
//void loadGame(TTF_Font &h1, TTF_Font *normal, SDL_Surface *Player1_sprite, SDL_Surface *player2_sprite, SDL_Surface *coins);

int game(SDL_Surface *screen);

void manageClick(SDL_Event &event, Player players[], int &current_turn, Map tiles);

Player getOtherPlayer(Player players[], int currentTurn);

int doesAPlayerWon(Player players[], Map tiles);

#endif
