#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include <deque>

class Food
{
private:
    Vector2 position;
    Vector2 getRandomPosition();

public:
    Food();
    void respawnFood(std::deque<Vector2> snakePositions);
    void drawFood();
    Vector2 getPosition();
};

#endif // FOOD_H