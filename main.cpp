#include "include/GameSettings.h"
#include "include/Food.h"
#include "include/Snake.h"
#include "include/raylib.h"
#include <iostream>

// Function prototypes
void InitializeWindow();
void DrawBackground();
void DrawComponents();
void ManageSnakeAppleCollision();

Food *food;
Snake *snake;

int main()
{
    // Initialize window
    InitializeWindow();

    // Initialize components
    food = new Food();
    snake = new Snake();

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawBackground();
        DrawComponents();
        ManageSnakeAppleCollision();

        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}

void DrawBackground()
{
    // Clear background
    ClearBackground(UI_BACKGROUND_COLOR);

    // Draw grid
    for (int i = 0; i <= GRID_X; i++)
    {
        DrawLine(GRID_PADDING + i * GRID_CELL_SIZE, GRID_PADDING, GRID_PADDING + i * GRID_CELL_SIZE, SCREEN_HEIGHT - GRID_PADDING, DARKGRAY);
    }

    for (int i = 0; i <= GRID_Y; i++)
    {
        DrawLine(GRID_PADDING, GRID_PADDING + i * GRID_CELL_SIZE, SCREEN_WIDTH - GRID_PADDING, GRID_PADDING + i * GRID_CELL_SIZE, DARKGRAY);
    }
}

void DrawComponents()
{
    // Draw food
    food->drawFood();

    // Draw snake
    snake->drawSnake();
}

void InitializeWindow()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
    SetTargetFPS(FPS);
}

void ManageSnakeAppleCollision()
{
    Vector2 headPosition = snake->getHeadPosition();
    Vector2 applePosition = food->getPosition();

    if (headPosition.x == applePosition.x && headPosition.y == applePosition.y)
    {
        food->respawnFood(snake->getPositionsOfSnake());
        snake->grow();
    }
}