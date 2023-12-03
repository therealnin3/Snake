#include "include/Snake.h"
#include "include/GameSettings.h"
#include "include/raylib.h"
#include <deque>

std::deque<Vector2> snakeBody;

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
    for (int i = 0; i < snakeBody.size(); i++)
    {
        DrawRectangle(GRID_PADDING + snakeBody[i].x * GRID_CELL_SIZE + COMPONENTS_PADDING, GRID_PADDING + snakeBody[i].y * GRID_CELL_SIZE + COMPONENTS_PADDING, COMPONENTS_SIZE, COMPONENTS_SIZE, SNAKE_COLOR);
    }
}

// Move snake
void Snake::move()
{
}

// Eat food
void Snake::eatFood()
{
}
