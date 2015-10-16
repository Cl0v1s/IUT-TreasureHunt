#ifndef ENTITY
#define ENTITY

#include "Lib.h"
struct Entity
{
    int x;
    int y;
    Vector2 velocity;
    int combo;
    int lastCoin;
    int points;
    bool isPlayer;
};

Entity createPlayer(int x, int y);
Entity createCoin(int x, int y, int value);

#endif // ENTITY
