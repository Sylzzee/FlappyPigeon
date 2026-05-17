#include "game_math.h"
#include "game_math_priv.h"
#include "game_math/game_pause.h"

static Uint64 last_time = 0;

GameFrameData processMath() {
    GameFrameData data;

    const Uint64 now = SDL_GetTicks();

    const float elapsed = ((float)(now - last_time)) / 1000.0f;

    data.score = GS_getAddscore();

    birdFall(elapsed);

    SDL_FRect birdRect;
    birdRect.x = BIRD_LEFT_MARGIN;
    birdRect.y = getBirdY();
    birdRect.w = BIRD_WIDTH;
    birdRect.h = BIRD_HEIGHT;
    data.birdRect = birdRect;

    updateColumn(elapsed);
    
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

    SDL_Rect window_size;
    window_size.x = 0;
    window_size.y = 0;
    window_size.w = WINDOW_WIDTH;
    window_size.h = WINDOW_HEIGHT;
    data.window_size = window_size;

    data.pause_focus = GP_getMenuFocus();
    data.pause = GP_isPauseTrue();
    checkGameOver();
    data.game_over = GP_isGameOverTrue();
    data.game_over_focus = GP_getGameOverMenuFocus();

    last_time = now;

    return data;
}