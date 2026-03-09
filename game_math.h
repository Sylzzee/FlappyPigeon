#include <stdbool.h>

static float column = 1;
static float bird = 0.5;
static float rect_hole = 0.5;
int addscore = 0;
static bool pause = false;
static bool game_over = false;
static bool flag = true;
static float column_speed = 0.18f;

int menu_focus = 1;
int game_over_focus = 1;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define COLUMN_WIDTH 60
#define HOLE_HEIGHT 60
#define BIRD_LEFT_MARGIN 120
#define BIRD_WIDTH 80
#define BIRD_HEIGHT 30
#define BIRD_RIGHT_X (BIRD_LEFT_MARGIN + BIRD_WIDTH)
#define PIXELS_PER_SECOND 60

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
    if (!pause)
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
    if (!pause)
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
    if (game_over)
    {
        switch (game_over_focus)
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
    if (pause)
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
