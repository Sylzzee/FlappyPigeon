#ifndef GAME_PAUSE_H
#define GAME_PAUSE_H

#include <stdbool.h>

struct GamePause {
    bool pause;
    bool game_over;
    int menu_focus;
    int game_over_focus;
};

void GP_switchPause();

void GP_gamePauseReset();

void GP_gameOverPause();

bool GP_isPauseTrue();

bool GP_isGameOverTrue();

int GP_getMenuFocus();

int GP_getGameOverMenuFocus();

void GP_rectFocusUp();

void GP_rectFocusDown();

void GP_gameOverRectFocusUp();

void GP_gameOverRectFocusDown();

#endif