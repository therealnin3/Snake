#include "include/Snake.h"
#include "include/GameSettings.h"
#include "include/raylib.h"
#include <deque>
#include <iostream>

Vector2 direction;
Vector2 tempDirection;
std::deque<Vector2> snakeBody;
float lastUpdateTime;
bool mustGrow;

// Constructor
Snake::Snake()
{
    // Starting variables
    direction = {0, 0};
    tempDirection = {0, 0};
    mustGrow = false;
    lastUpdateTime = 0;

    Vector2 startingPos = {(int)(GRID_X / 2), (int)(GRID_Y / 2)};
    snakeBody.push_back(startingPos);
    snakeBody.push_back({startingPos.x, startingPos.y + 1});
    snakeBody.push_back({startingPos.x, startingPos.y + 2});
}

// Destructor
Snake::~Snake()
{
}

// Draw snake
void Snake::drawSnake()
{
    // Change position
    move();

    // Draw new position
    for (int i = 0; i < snakeBody.size(); i++)
    {
        DrawRectangle(snakeBody[i].x * GRID_CELL_SIZE + GRID_PADDING, snakeBody[i].y * GRID_CELL_SIZE + GRID_PADDING, GRID_CELL_SIZE, GRID_CELL_SIZE, GREEN);
    }
}

// Move snake
void Snake::move()
{

    // Get input
    if (IsKeyPressed(KEY_UP))
    {
        tempDirection = {0, -1};
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        tempDirection = {0, 1};
    }
    else if (IsKeyPressed(KEY_LEFT))
    {
        tempDirection = {-1, 0};
    }
    else if (IsKeyPressed(KEY_RIGHT))
    {
        tempDirection = {1, 0};
    }

    // Update snake position
    if (GetTime() - lastUpdateTime > SNAKE_INTERVAL_TIME)
    {
        lastUpdateTime = GetTime();

        // TODO: check temp and direction

        // if (mustGrow)
        // {
        //     // Handle snake growth
        //     snakeBody.push_front({snakeBody[0].x + tempDirection.x, snakeBody[0].y + tempDirection.y});
        //     mustGrow = false;
        // }
        // else
        // {
        //     // Handle snake movement
        //     snakeBody.pop_back();
        //     snakeBody.push_front({snakeBody[0].x + tempDirection.x, snakeBody[0].y + tempDirection.y});
        // }

        // Check for collide after move
        if (isCollidingWithSelf())
        {
            // Game Over
            std::cout << "Game Over" << std::endl;
        }

        // Update direction and reset tempDirection
        direction = tempDirection;
        tempDirection = {0, 0};
    }
}

// Check if snake is colliding with itself
bool Snake::isCollidingWithSelf()
{
    for (int i = 1; i < snakeBody.size(); i++)
    {
        if (snakeBody[0].x == snakeBody[i].x && snakeBody[0].y == snakeBody[i].y)
        {
            return true;
        }
    }

    return false;
}

// Get snake head position
Vector2 Snake::getHeadPosition()
{
    return {snakeBody[0].x, snakeBody[0].y};
}

// Grow snake
void Snake::grow()
{
    mustGrow = true;
}

// Get snake positions
std::deque<Vector2> Snake::getPositionsOfSnake()
{
    return snakeBody;
}
