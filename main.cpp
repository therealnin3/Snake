#include "include/GameSettings.h"
#include "include/Food.h"
#include <iostream>
#include "include/raylib.h"

// Function prototypes
void InitializeWindow();
void DrawBackground();
void DrawComponents();

Food *food;

int main()
{
    // Initialize window
    InitializeWindow();

    food = new Food();

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawBackground();
        food->drawFood();

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
    // food.drawFood();

    // Draw snake
}

void InitializeWindow()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
    SetTargetFPS(FPS);
}
