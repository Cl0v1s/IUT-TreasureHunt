#include "Entity.h"

Entity createPlayer(int x, int y)
{
    Entity player;
    player.x = x;
    player.y = y;
    player.points = 0;
    player.lastCoin = 0;
    Vector2 velocity;
    velocity.x = 0.0;
    velocity.y = 0.0;
    player.velocity = velocity;
    player.combo = 0;
    player.isPlayer = true;
    return player;
}

Entity createCoin(int x, int y, int value)
{
    Entity coin;
    coin.x = x;
    coin.y = y;
    coin.points = value;
    coin.lastCoin = 0;
    Vector2 velocity;
    velocity.x = 0.0;
    velocity.y = 0.0;
    coin.velocity = velocity;
    coin.combo = 0;
    coin.isPlayer = false;
    return coin;
}
