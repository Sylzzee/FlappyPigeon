#include "game_math.h"
#include "game_math_priv.h"
#include "game_math/game_pause.h"

GameFrameData processMath() {
    GameFrameData data;

    data.score = GS_getAddscore();

    SDL_FRect birdRect;
    birdRect.x = BIRD_LEFT_MARGIN;
    birdRect.y = getBirdY();
    birdRect.w = BIRD_WIDTH;
    birdRect.h = BIRD_HEIGHT;
    data.birdRect = birdRect;
    
    SDL_FRect column1;
    column1.x = GC_getColumnX();
    column1.y = 0;
    column1.w = COLUMN_WIDTH;
    column1.h = GC_getHoleTopY();
    data.columnTop = column1;

    SDL_FRect column2;
    column2.x = GC_getColumnX();
    column2.y = GC_getHoleBottomY();
    column2.w = COLUMN_WIDTH;
    column2.h = WINDOW_HEIGHT - GC_getHoleBottomY();
    data.columnBottom = column2;

    data.pause_focus = GP_getMenuFocus();
    data.pause = GP_isPauseTrue();
    data.game_over = GP_isGameOverTrue();
    data.game_over_focus = GP_getGameOverMenuFocus();

    return data;
}