#include "include/Food.h"
#include "include/GameSettings.h"
#include "include/raylib.h"

// Constructor
Food::Food(std::deque<Vector2> snakePositions)
{
    respawnFood(snakePositions);
}

// Respawn food at a random location
void Food::respawnFood(std::deque<Vector2> snakePositions)
{
    bool foundPosition = false;
    while (!foundPosition)
    {
        // Get random position
        Vector2 pos = getRandomPosition();

        // Check if position is not occupied by snake
        bool isOccupied = false;
        for (int i = 0; i < snakePositions.size(); i++)
        {
            if (snakePositions[i].x == pos.x && snakePositions[i].y == pos.y)
            {
                isOccupied = true;
                break;
            }
        }

        // If position is not occupied, set position
        if (!isOccupied)
        {
            this->position = pos;
            foundPosition = true;
        }
    }

    // DrawFood
    drawFood();
}

Vector2 Food::getRandomPosition()
{
    Vector2 position = {0, 0};
    position.x = GetRandomValue(0, GRID_X - 1);
    position.y = GetRandomValue(0, GRID_Y - 1);

    return position;
}

void Food::drawFood()
{
    DrawRectangle(this->position.x * GRID_CELL_SIZE + GRID_PADDING + FOOD_PADDING, this->position.y * GRID_CELL_SIZE + GRID_PADDING + FOOD_PADDING, GRID_CELL_SIZE * FOOD_SCALE, GRID_CELL_SIZE * FOOD_SCALE, FOOD_COLOR);
}

Vector2 Food::getPosition()
{
    return this->position;
}
