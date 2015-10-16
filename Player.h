#ifndef Player_H
#define Player_H

#include <SDL/SDL.h>
#include <cmath>
#include <climits>
#include "Lib.h"
#include "Map.h"


/* *********************** Nom de la structure ************************
* Player
*************************** Auteur, Dates ****************************
* C. Portron, 19/11/14
*************************** Description ******************************
* Joueur
*************************** valeurs **********************************
* id, id du joueur
* sprite, feuille de sprite du joueur
* position, position (en pixels du joueur)
* coords, position en cases du joueur
* velocity, vecteur appliqué à la position pour dé"placer le joueur
* target, case devant etre atteinte par le joueur (pour les déplacement)
* points, points du joueur
* combo, nombre de combo actuel
* lastcoin, dernière pice ramassée par le joueur
* frame, index utilisé pour l'animation
* turn, nombre de tour joués par le joueur
**********************************************************************/
struct Player
{
    int id;
    SDL_Surface *sprite;
    Vector2 position;
    Vector2 coords;
    Vector2 velocity;
    Vector2 target;
    int points;
    int combo;
    int lastCoin;
    float frame;
    int turn;
};

Player createPlayer(int id, Vector2 position, SDL_Surface *sprite);

void stop(Player &player);

bool updatePlayer(Player &player, Map tiles);

void replacePlayer(Player *player);

void movePlayer(Player &player, Vector2 destination, Map tiles);

void drawPlayer(Player player, SDL_Surface *screen);

bool getCoinPlayer(Player &player, Map tiles);


#endif
