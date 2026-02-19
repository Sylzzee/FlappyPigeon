#include <stdbool.h>

static float column = 1;
static float bird = 0.5;
static int game_over = 0;
static float rect_hole = 0.5;
int addscore = 0;
static float pause = 0;
static bool flag = 1;
static float column_speed = 0.18f;

int rect_focus = 1;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define COLUMN_WIDTH 60
#define HOLE_HEIGHT 60
#define BIRD_LEFT_MARGIN 120
#define BIRD_WIDTH 80
#define BIRD_HEIGHT 30
#define BIRD_RIGHT_X (BIRD_LEFT_MARGIN + BIRD_WIDTH)
#define PIXELS_PER_SECOND 60

void birdLimit()
{
    if (bird > 1)
    {
        game_over = 1;
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
    rect_focus--;
    if (rect_focus < 1)
    {
        rect_focus = 3;
    }
}

void rectFocusDown()
{
    rect_focus++;
    if (rect_focus > 3)
    {
        rect_focus = 1;
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
    if (isBirdOvercomeColumn())
    {
        if (isBirdInsideHole())
        {
            game_over = 0;
        }
        else
        {
            game_over = 1;
        }
    }
}

bool isGameNotOver()
{
    return game_over == 0;
}

void restart()
{
    pause = 0;
    addscore = 0;
    bird = 0.5;
    column = 1;
}

SDL_AppResult processMenu()
{
    if (rect_focus == 1 && pause)
    {
        pause = !pause;
    }
    else if (rect_focus == 2)
    {
        restart();
    }
    else if (rect_focus == 3)
    {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}
