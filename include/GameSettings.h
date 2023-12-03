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
        30, 30, 30, 255     \
    }

// Grid Settings
#define GRID_CELL_SIZE 30
#define GRID_X 25
#define GRID_Y 25
#define GRID_PADDING 30

// Snake Settings
#define SNAKE_INTERVAL_TIME 0.2
#define SNAKE_COLOR      \
    {                    \
        50, 219, 23, 255 \
    }

// Food Settings
#define FOOD_COLOR RED

#endif // GAME_SETTINGS_H