#include "game_pause.h"

static struct GamePause gamePause;

void GP_switchPause()
{
    if (gamePause.tap_to_start == true) 
    {
        return;
    }
    if (gamePause.game_over == false)
    {
        gamePause.pause = !gamePause.pause;
        gamePause.tap_to_start = false;
        gamePause.menu_focus = 1;
    }
}

void GP_gamePauseReset()
{
    gamePause.pause = false;
    gamePause.game_over = false;
    gamePause.tap_to_start = false;
    gamePause.menu_focus = 1;
    gamePause.game_over_focus = 1;
}

void GP_gameOverPause()
{
    gamePause.pause = true;
    gamePause.game_over = true;
    gamePause.game_over_focus = 1;
}

bool GP_isPauseTrue()
{
    return gamePause.pause;
}

bool GP_isGameOverTrue()
{
    return gamePause.game_over;
}

bool GP_isTapToStartTrue()
{
    return gamePause.tap_to_start;
}

void GP_showTapToStart()
{
    gamePause.tap_to_start = true;
    gamePause.pause = true;
    gamePause.menu_focus = 1;
}

int GP_getMenuFocus()
{
    return gamePause.menu_focus;
}

int GP_getGameOverMenuFocus()
{
    return gamePause.game_over_focus;
}

void GP_rectFocusUp()
{
    gamePause.menu_focus--;
    if (gamePause.menu_focus < 1)
    {
        gamePause.menu_focus = 3;
    }
}

void GP_rectFocusDown()
{
    gamePause.menu_focus++;
    if (gamePause.menu_focus > 3)
    {
        gamePause.menu_focus = 1;
    }
}

void GP_gameOverRectFocusUp()
{
    gamePause.game_over_focus--;
    if (gamePause.game_over_focus < 1)
    {
        gamePause.game_over_focus = 2;
    }
}

void GP_gameOverRectFocusDown()
{
    gamePause.game_over_focus++;
    if (gamePause.game_over_focus > 2)
    {
        gamePause.game_over_focus = 1;
    }
}

