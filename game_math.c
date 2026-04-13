#include "game_math.h"

static float column = 1;
static float bird = 0.5;
static float rect_hole = 0.5;
static float column_speed = 0.18f;
static bool flag = true;
static bool pause = false;
static bool game_over = false;
static int menu_focus = 1;
static int game_over_focus = 1;
static int addscore = 0;

void switchPause() {
    pause = !pause;
    menu_focus = 1;
}

bool isPauseTrue() {
    return pause;
}

bool isGameOverTrue() {
    return game_over;
}

int getMenuFocus() {
    return menu_focus;
}

int getGameOverMenuFocus() {
    return game_over_focus;
}

int getAddscore() {
    return addscore;
}

void restart()
{
    pause = false;
    addscore = 0;
    bird = 0.5;
    column = 1;
    game_over = false;
}

void gameOverPause()
{
    pause = true;
    game_over = true;
    game_over_focus = 1;
}

void birdLimit()
{
    if (bird > 1)
    {
        gameOverPause();
    }
    else if (bird < 0)
    {
        bird = 0;
    }
}

float getColumnX()
{
    return column * WINDOW_WIDTH;
}

float getHoleTopY()
{
    return rect_hole * WINDOW_HEIGHT;
}

float getHoleBottomY()
{
    return getHoleTopY() + HOLE_HEIGHT * 2;
}

float getBirdY()
{
    return bird * WINDOW_HEIGHT;
}

float getColumnRightX()
{
    return getColumnX() + COLUMN_WIDTH;
}

float getBirdBottomY()
{
    return getBirdY() + BIRD_HEIGHT;
}

void updateColumn(const float elapsed)
{
    if (!isPauseTrue())
    {
        column -= column_speed * elapsed;
        if (getColumnRightX() < BIRD_LEFT_MARGIN)
        {
            if (flag == 1)
            {
                addscore++;
                flag = 0;
            }
        }
    }

    if (column <= -COLUMN_WIDTH / WINDOW_WIDTH)
    {
        column = 1;
        flag = 1;
        rect_hole = SDL_randf() * ((float)(WINDOW_HEIGHT - HOLE_HEIGHT) / WINDOW_HEIGHT);
    }
}

bool isBirdOvercomeColumn()
{
    return BIRD_RIGHT_X <= getColumnRightX() && BIRD_RIGHT_X >= getColumnX() ||
           BIRD_LEFT_MARGIN <= getColumnRightX() && BIRD_LEFT_MARGIN >= getColumnX();
}

bool isBirdInsideHole()
{
    bool top = getBirdY() > getHoleTopY();
    bool bottom = getBirdBottomY() < getHoleBottomY();
    return top && bottom;
}

void rectFocusUp()
{
    menu_focus--;
    if (menu_focus < 1)
    {
        menu_focus = 3;
    }
}

void rectFocusDown()
{
    menu_focus++;
    if (menu_focus > 3)
    {
        menu_focus = 1;
    }
}

void gameOverRectFocusUp()
{
    game_over_focus--;
    if (game_over_focus < 1)
    {
        game_over_focus = 2;
    }
}

void gameOverRectFocusDown()
{
    game_over_focus++;
    if (game_over_focus > 2)
    {
        game_over_focus = 1;
    }
}

void birdUp()
{
    bird -= 0.1f;
    birdLimit();
}

void birdDown()
{
    bird += 0.1f;
    birdLimit();
}

void birdFall(const float elapsed)
{
    if (!isPauseTrue())
    {
        bird += 0.1f * elapsed;
        birdLimit();
    }
}

void checkGameOver()
{
    if (isBirdOvercomeColumn() && !isBirdInsideHole())
    {
        gameOverPause();
    }
}

SDL_AppResult processGameOverMenu()
{
    if (isGameOverTrue())
    {
        switch (getGameOverMenuFocus())
        {
        case 1:
            restart();
            break;
        case 2:
            return SDL_APP_SUCCESS;
            break;
        default:
            break;
        }
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult processMenu()
{
    if (isPauseTrue())
    {
        switch (menu_focus)
        {
        case 1:
            pause = false;
            break;
        case 2:
            restart();
            break;
        case 3:
            return SDL_APP_SUCCESS;
            break;
        default:
            break;
        }
    }
    return SDL_APP_CONTINUE;
}