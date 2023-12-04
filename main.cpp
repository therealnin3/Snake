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
void ManageWinCondition();

Food *food;
Snake *snake;

int main()
{
    // Initialize window
    InitializeWindow();

    // Initialize components
    snake = new Snake();
    food = new Food(snake->getPositionsOfSnake());

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawBackground();
        DrawComponents();
        ManageSnakeAppleCollision();
        ManageWinCondition();

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

    // Draw vertical grid lines
    for (int i = 0; i < GRID_X + 1; i++)
    {
        DrawLine(GRID_PADDING + i * GRID_CELL_SIZE, GRID_PADDING, GRID_PADDING + i * GRID_CELL_SIZE, GRID_PADDING + GRID_CELL_SIZE * GRID_Y, GRID_COLOR);
    }

    // Draw horizontal grid lines
    for (int i = 0; i < GRID_Y + 1; i++)
    {
        DrawLine(GRID_PADDING, GRID_PADDING + i * GRID_CELL_SIZE, GRID_PADDING + GRID_CELL_SIZE * GRID_X, GRID_PADDING + i * GRID_CELL_SIZE, GRID_COLOR);
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

void ManageWinCondition()
{
    if (snake->isSnakeAlive() == false)
    {
        std::cout << "You died!" << std::endl;

        // Restart game
        delete food;
        delete snake;
        snake = new Snake();
        food = new Food(snake->getPositionsOfSnake());
    }
}