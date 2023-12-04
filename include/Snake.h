#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "raylib.h"

class Snake
{
private:
    std::deque<Vector2> snakeBody;
    Vector2 direction;
    double lastUpdateTime;
    bool isCollidingWithSelf();
    bool mustGrow;
    void playDeathAnimation();
    bool deathAnimationPlaying;

public:
    Snake();
    ~Snake();

    void move();
    void drawSnake();
    Vector2 getHeadPosition();
    void grow();
    std::deque<Vector2> getPositionsOfSnake();
    bool isSnakeAlive();
};

#endif // SNAKE_H
