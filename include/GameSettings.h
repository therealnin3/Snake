#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

// Window Settings
#define WINDOW_NAME "Snake"
#define SCREEN_WIDTH GRID_CELL_SIZE *GRID_X + GRID_PADDING * 2
#define SCREEN_HEIGHT GRID_CELL_SIZE *GRID_Y + GRID_PADDING * 2
#define FPS 60

// UI Settings
#define UI_FONT_SIZE 20
#define UI_FONT_COLOR    \
    {                    \
        50, 219, 23, 255 \
    }
#define UI_BACKGROUND_COLOR \
    {                       \
        19, 19, 19, 255     \
    }

// Grid Settings
#define GRID_COLOR      \
    {                   \
        39, 73, 33, 255 \
    }
#define GRID_THICKNESS 2
#define GRID_CELL_SIZE 30
#define GRID_X 20
#define GRID_Y 20
#define GRID_PADDING 30

// Snake Settings
#define SNAKE_INTERVAL_TIME 0.2
#define SNAKE_COLOR      \
    {                    \
        50, 219, 23, 255 \
    }

// Food Settings
#define FOOD_COLOR SNAKE_COLOR
#define FOOD_SCALE 0.3
#define FOOD_PADDING (GRID_CELL_SIZE - (GRID_CELL_SIZE * FOOD_SCALE)) / 2
#define FOOD_SCORE 10

#endif // GAME_SETTINGS_H