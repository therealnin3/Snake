#include "include/Snake.h"
#include "include/GameSettings.h"
#include "include/raylib.h"
#include <deque>

Vector2 direction = {0, 0};
std::deque<Vector2> snakeBody;
float lastUpdateTime = 0;
bool mustGrow = false;

// Constructor
Snake::Snake()
{
    // Starting positions
    snakeBody.push_back({GRID_X / 2, GRID_Y / 2});
    snakeBody.push_back({GRID_X / 2, GRID_Y / 2 + 1});
    snakeBody.push_back({GRID_X / 2, GRID_Y / 2 + 2});
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
        Rectangle r = {float(GRID_PADDING + snakeBody[i].x * GRID_CELL_SIZE + COMPONENTS_PADDING), float(GRID_PADDING + snakeBody[i].y * GRID_CELL_SIZE + COMPONENTS_PADDING), COMPONENTS_SIZE, COMPONENTS_SIZE};
        DrawRectangleRounded(r, 0.25f, 0, SNAKE_COLOR);
    }
}

// Move snake
void Snake::move()
{
    // Get input
    if (IsKeyPressed(KEY_UP) && direction.y != 1)
    {
        direction = {0, -1};
    }
    else if (IsKeyPressed(KEY_DOWN) && direction.y != -1)
    {
        direction = {0, 1};
    }
    else if (IsKeyPressed(KEY_LEFT) && direction.x != 1)
    {
        direction = {-1, 0};
    }
    else if (IsKeyPressed(KEY_RIGHT) && direction.x != -1)
    {
        direction = {1, 0};
    }

    // Don't move if no input
    if (direction.x == 0 && direction.y == 0)
    {
        return;
    }

    // Update snake position
    if (GetTime() - lastUpdateTime > SNAKE_INTERVAL_TIME)
    {
        lastUpdateTime = GetTime();

        if (mustGrow)
        {
            // Handle snake growth
            snakeBody.push_front({snakeBody[0].x + direction.x, snakeBody[0].y + direction.y});
            mustGrow = false;
        }
        else
        {
            // Handle snake movement
            snakeBody.pop_back();
            snakeBody.push_front({snakeBody[0].x + direction.x, snakeBody[0].y + direction.y});
        }

        // Check for collide after move
        if (isCollidingWithSelf())
        {
            // Game Over
            snakeBody.clear();
            snakeBody.push_back({GRID_X / 2, GRID_Y / 2});
            snakeBody.push_back({GRID_X / 2, GRID_Y / 2 + 1});
            snakeBody.push_back({GRID_X / 2, GRID_Y / 2 + 2});
        }
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