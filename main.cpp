#include "include/GameSettings.h"
#include "include/Food.h"
#include "include/Snake.h"
#include "include/raylib.h"
#include <iostream>
#include <iomanip>

// Function prototypes
void InitializeWindow();
void DrawBackground();
void DrawComponents();
void ManageSnakeAppleCollision();
void ManageWinCondition();

Food *food;
Snake *snake;

int Score;
int HighScore;

int main()
{
    // Initialize window
    InitializeWindow();

    // Initialize components
    Score = 0;
    HighScore = 0;
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

    // Draw UI background
    DrawRectangleLines(SCREEN_WIDTH - UI_SECTION_WIDTH, GRID_PADDING, UI_SECTION_WIDTH - GRID_PADDING, SCREEN_HEIGHT - 2 * GRID_PADDING, GRID_COLOR);
    Vector2 TopLeftCornerWithMargin = {SCREEN_WIDTH - UI_SECTION_WIDTH + 20, GRID_PADDING + 20};
    Vector2 BottomLeftCornerWithMargin = {SCREEN_WIDTH - UI_SECTION_WIDTH + 20, SCREEN_HEIGHT - 2 * GRID_PADDING};

    // Draw UI text
    int SpaceBetweenLines = 30;
    DrawText(("Score: " + std::to_string(Score)).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 0 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    DrawText(("HighScore: " + std::to_string(HighScore)).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 1 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);

    DrawText(("Grid x: " + std::to_string(GRID_X)).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 3 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    DrawText(("Grid y: " + std::to_string(GRID_Y)).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 4 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << SNAKE_INTERVAL_TIME;
    DrawText(("Snake_Interval: " + stream.str()).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 5 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    DrawText(("FPS: " + std::to_string(GetFPS())).c_str(), TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 6 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);

    DrawText("Controls:", TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 10 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    DrawText("UpArrow/DownArrow:", TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 11 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
    DrawText("LeftArrow/RightArrow:", TopLeftCornerWithMargin.x, TopLeftCornerWithMargin.y + 12 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);

    DrawText("Classic snake by nin3.", BottomLeftCornerWithMargin.x, BottomLeftCornerWithMargin.y - 0 * SpaceBetweenLines, UI_FONT_SIZE, UI_FONT_COLOR);
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
        Score += FOOD_SCORE;

        if (Score > HighScore)
        {
            HighScore = Score;
        }

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
        Score = 0;
    }
}