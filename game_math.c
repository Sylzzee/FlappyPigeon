#include "game_math.h"
#include "game_math/game_pause.h"
#include "game_math/game_score.h"
#include "game_math/game_columnState.h"

static float bird = 0.5;

void initState()
{
    GC_initState();
    GS_scoreFlagTrue();
    GS_addscoreReset();
    GP_gamePauseReset();
}

void restart()
{
    GP_gamePauseReset();
    GS_addscoreReset();
    bird = 0.5;
    GC_initState();
}

void birdLimit()
{
    if (bird > 1)
    {
        GP_gameOverPause();
    }
    else if (bird < 0)
    {
        bird = 0;
    }
}

float getBirdY()
{
    return bird * WINDOW_HEIGHT;
}

float getBirdBottomY()
{
    return getBirdY() + BIRD_HEIGHT;
}

void updateColumn(const float elapsed)
{
    if (!GP_isPauseTrue())
    {
        GC_moveColumn(elapsed);
        if (GC_getColumnRightX() < BIRD_LEFT_MARGIN)
        {
            if (GS_isScoreFlagTrue())
            {
                GS_addScore();
                GS_changeScoreFlag();
            }
        }
    }

    if (GC_getColumnState() <= -COLUMN_WIDTH / WINDOW_WIDTH)
    {
        GC_columnStateReset();
        GS_scoreFlagTrue();
        GC_randRectHole();
    }
}

bool isBirdOvercomeColumn()
{
    return BIRD_RIGHT_X <= GC_getColumnRightX() && BIRD_RIGHT_X >= GC_getColumnX() ||
           BIRD_LEFT_MARGIN <= GC_getColumnRightX() && BIRD_LEFT_MARGIN >= GC_getColumnX();
}

bool isBirdInsideHole()
{
    bool top = getBirdY() > GC_getHoleTopY();
    bool bottom = getBirdBottomY() < GC_getHoleBottomY();
    return top && bottom;
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
    if (!GP_isPauseTrue())
    {
        bird += 0.1f * elapsed;
        birdLimit();
    }
}

void checkGameOver()
{
    if (isBirdOvercomeColumn() && !isBirdInsideHole())
    {
        GP_gameOverPause();
    }
}

SDL_AppResult processMenu()
{
    if (GP_isPauseTrue())
    {
        switch (GP_getMenuFocus())
        {
        case 1:
            GP_gamePauseReset();
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

SDL_AppResult processGameOverMenu()
{
    if (GP_isGameOverTrue())
    {
        switch (GP_getGameOverMenuFocus())
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