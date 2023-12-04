#include "include/Snake.h"
#include "include/GameSettings.h"
#include "include/raylib.h"
#include <deque>
#include <iostream>
#include <synchapi.h>
#include <thread>

Vector2 direction;
Vector2 currentDirection;
std::deque<Vector2> snakeBody;
float lastUpdateTime;
bool mustGrow;
bool snakeIsAlive;

// Constructor
Snake::Snake()
{
    // Starting variables
    deathAnimationPlaying = false;
    snakeIsAlive = true;
    direction = {0, 0};
    currentDirection = {0, 0};
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

void Snake::move()
{
    // Get input
    if (IsKeyPressed(KEY_UP) && currentDirection.y != 1)
    {
        direction = {0, -1};
    }
    else if (IsKeyPressed(KEY_DOWN) && currentDirection.y != -1)
    {
        direction = {0, 1};
    }
    else if (IsKeyPressed(KEY_LEFT) && currentDirection.x != 1)
    {
        direction = {-1, 0};
    }
    else if (IsKeyPressed(KEY_RIGHT) && currentDirection.x != -1)
    {
        direction = {1, 0};
    }

    // Only move snake if key is pressed
    if (direction.x != 0 || direction.y != 0)
    {
        // Update snake position
        if (GetTime() - lastUpdateTime > SNAKE_INTERVAL_TIME)
        {
            // Enter legal interval
            lastUpdateTime = GetTime();

            currentDirection.x = direction.x;
            currentDirection.y = direction.y;

            // Calculate new head position
            Vector2 newHead = {snakeBody[0].x + currentDirection.x, snakeBody[0].y + currentDirection.y};

            // Check for collisions with walls and itself
            if (isCollidingWithWall(newHead) || isCollidingWithSelf(newHead))
            {
                // Game Over
                std::cout << "Game Over" << std::endl;
                snakeIsAlive = false;
                playDeathAnimation();
                while (deathAnimationPlaying)
                {
                    // hang
                }
            }
            else
            {
                // Handle snake movement and growth
                snakeBody.push_front(newHead);

                if (mustGrow)
                {
                    mustGrow = false;
                }
                else
                {
                    snakeBody.pop_back();
                }
            }
        }
    }
}

// Check if snake is colliding with wall at the given position
bool Snake::isCollidingWithWall(const Vector2 &position)
{
    return (position.x < 0 || position.x >= GRID_X || position.y < 0 || position.y >= GRID_Y);
}

// Check if snake is colliding with itself at the given position
bool Snake::isCollidingWithSelf(const Vector2 &position)
{
    for (const auto &bodyPart : snakeBody)
    {
        if (position.x == bodyPart.x && position.y == bodyPart.y)
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

// Play death animation
void Snake::playDeathAnimation()
{
    deathAnimationPlaying = true;
    float flicker_interval_seconds = 0.25f; // Change to float
    int flicker_times = 5;

    for (int i = 0; i < flicker_times; i++)
    {
        // Flicker snake
        for (int i = 0; i < snakeBody.size(); i++)
        {
            DrawRectangle(snakeBody[i].x * GRID_CELL_SIZE + GRID_PADDING, snakeBody[i].y * GRID_CELL_SIZE + GRID_PADDING, GRID_CELL_SIZE, GRID_CELL_SIZE, WHITE);
        }

        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(flicker_interval_seconds * 1000)));

        BeginDrawing(); // Restart drawing

        // Flicker snake
        for (int i = 0; i < snakeBody.size(); i++)
        {
            DrawRectangle(snakeBody[i].x * GRID_CELL_SIZE + GRID_PADDING, snakeBody[i].y * GRID_CELL_SIZE + GRID_PADDING, GRID_CELL_SIZE, GRID_CELL_SIZE, SNAKE_COLOR);
        }

        EndDrawing();
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(flicker_interval_seconds * 1000)));

        BeginDrawing(); // Restart drawing
    }

    deathAnimationPlaying = false;
}
bool Snake::isSnakeAlive()
{
    return snakeIsAlive;
}
