#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include "game_math.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static char background_path[] = "background.bmp";
static char bird_path[] = "Bird.bmp";
static char column_path[] = "column.bmp";
static SDL_Texture *background_texture = NULL;
static SDL_Texture *bird_texture = NULL;
static SDL_Texture *column_texture = NULL;
static Uint64 last_time = 0;

#define MENURECT_LEFT_MARGIN 160
#define MENURECT_WIDTH 320
#define MENURECT_HEIGHT 60
#define TEXT_SIZE 20

SDL_AppResult Game_Init()
{
    if (!SDL_CreateWindowAndRenderer("examples/renderer/rectangles", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_Surface *surface = NULL;

    surface = SDL_LoadBMP(background_path);
    if (!surface)
    {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    background_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!background_texture)
    {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);

    surface = SDL_LoadBMP(bird_path);
    if (!surface)
    {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    bird_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!bird_texture)
    {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);

    surface = SDL_LoadBMP(column_path);
    if (!surface)
    {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    column_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!column_texture)
    {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);

    return SDL_APP_CONTINUE;
}

void drawBackground()
{
    SDL_FRect background;
    background.x = 0;
    background.y = 0;
    background.w = WINDOW_WIDTH;
    background.h = WINDOW_HEIGHT;
    SDL_RenderTexture(renderer, background_texture, NULL, &background);
}

void drawColumn()
{
    SDL_FRect column1;
    column1.x = getColumnX();
    column1.y = 0;
    column1.w = COLUMN_WIDTH;
    column1.h = getHoleTopY();
    SDL_RenderTexture(renderer, column_texture, NULL, &column1);

    SDL_FRect column2;
    column2.x = getColumnX();
    column2.y = getHoleBottomY();
    column2.w = COLUMN_WIDTH;
    column2.h = WINDOW_HEIGHT - getHoleBottomY();
    SDL_RenderTexture(renderer, column_texture, NULL, &column2);
}

void drawBird()
{
    SDL_FRect birdRect;
    birdRect.x = BIRD_LEFT_MARGIN;
    birdRect.y = getBirdY();
    birdRect.w = BIRD_WIDTH;
    birdRect.h = BIRD_HEIGHT;
    SDL_RenderTexture(renderer, bird_texture, NULL, &birdRect);
}

void drawRectFocus(int i) {
    SDL_SetRenderDrawColor(renderer, 255, 60, 60, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRectChooseUp;
    //for (i; i > -1; i--) {
        menuRectChooseUp.x = MENURECT_LEFT_MARGIN - 5;
        menuRectChooseUp.y = 90 * i - 5;
        menuRectChooseUp.w = MENURECT_WIDTH + 10;
        menuRectChooseUp.h = MENURECT_HEIGHT + 10;
        SDL_RenderFillRect(renderer, &menuRectChooseUp);
    //}
}

void RectChooseDown(int i) {
    SDL_SetRenderDrawColor(renderer, 255, 60, 60, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRectChooseDown;
    //for (i; i < 3; i++) {
        menuRectChooseDown.x = MENURECT_LEFT_MARGIN - 5;
        menuRectChooseDown.y = 90 * i - 5;
        menuRectChooseDown.w = MENURECT_WIDTH + 10;
        menuRectChooseDown.h = MENURECT_HEIGHT + 10;
        SDL_RenderFillRect(renderer, &menuRectChooseDown);
    //}
}

void drawMenuRects()
{
    SDL_SetRenderDrawColor(renderer, 255, 130, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRect;
    for (int i = 0; i < 3; i++)
    {
        menuRect.x = MENURECT_LEFT_MARGIN;
        menuRect.y = 90 + 90 * i;
        menuRect.w = MENURECT_WIDTH;
        menuRect.h = MENURECT_HEIGHT;
        SDL_RenderFillRect(renderer, &menuRect);
    }
}

void drawScore()
{
    char drawscore[100];
    SDL_SetRenderDrawColor(renderer, 180, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, 5.0f, 5.0f);
    snprintf(drawscore, 100, "%d", addscore);
    SDL_RenderDebugText(renderer, 60.6f, 2, drawscore);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void drawMenuText(const Uint64 now)
{
    char score[100];
    SDL_SetRenderScale(renderer, 3.5f, 3.5f);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 60, 31, "Continue");
    SDL_RenderDebugText(renderer, 64, 57, "Restart");
    SDL_RenderDebugText(renderer, 76, 82, "Exit");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void processBird(const float elapsed) {
    birdFall(elapsed);
    drawBird();
}

void processColumn(const float elapsed) {
    updateColumn(elapsed);
    drawColumn();
}

void drawMenu(const Uint64 now) {
    if (pause)
    {
        drawRectFocus(rect_focus);
        drawMenuRects();
        drawMenuText(now);
    }
}

void gameRender() {
    const Uint64 now = SDL_GetTicks();

    const float elapsed = ((float)(now - last_time)) / 1000.0f;

    drawBackground();

    processBird(elapsed);

    processColumn(elapsed);

    drawMenu(now);

    checkGameOver();

    drawScore();

    last_time = now;

    SDL_RenderPresent(renderer);
}