#include "raylib.h"

#ifndef FOOD_H
#define FOOD_H

class Food
{
private:
    Vector2 position;
    Vector2 getRandomPosition();

public:
    Food();
    void respawnFood();
    void drawFood();
};

#endif // FOOD_H