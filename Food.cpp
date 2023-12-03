#include "include/Food.h"
#include "include/GameSettings.h"
#include "include/raylib.h"

// Constructor
Food::Food()
{
    respawnFood();
}

// Respawn food at a random location
void Food::respawnFood()
{
    // Get random position
    this->position = getRandomPosition();

    // DrawFood
    drawFood();
}

Vector2 Food::getRandomPosition()
{
    Vector2 position = {0, 0};
    position.x = GetRandomValue(0, GRID_X - 1) * GRID_CELL_SIZE + GRID_PADDING;
    position.y = GetRandomValue(0, GRID_Y - 1) * GRID_CELL_SIZE + GRID_PADDING;

    return position;
}

void Food::drawFood()
{
    DrawRectangle(position.x + COMPONENTS_PADDING, position.y + COMPONENTS_PADDING, COMPONENTS_SIZE, COMPONENTS_SIZE, FOOD_COLOR);
}
