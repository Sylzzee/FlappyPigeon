#include "render.h"
#include <stdio.h>
#include "game_math.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static char background_path[] = "background.bmp";
static char bird_path[] = "Bird.png";
static char bird1_path[] = "Bird1.png";
static char column_path[] = "column.png";
static SDL_Texture *background_texture = NULL;
static SDL_Texture *bird_texture = NULL;
static SDL_Texture *bird1_texture = NULL;
static SDL_Texture *column_texture = NULL;
static int frame = 1;

SDL_AppResult Game_Init(const GameFrameData data)
{
    if (!SDL_CreateWindowAndRenderer("examples/renderer/rectangles", data.window_size.w, data.window_size.h, 0, &window, &renderer))
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

    surface = IMG_Load(bird_path);
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

    surface = IMG_Load(bird1_path);
    if (!surface)
    {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    bird1_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!bird1_texture)
    {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);

    surface = IMG_Load(column_path);
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

void drawBackground(const GameFrameData data)
{
    SDL_FRect window_size;
    window_size.x = (float)data.window_size.x;
    window_size.y = (float)data.window_size.y;
    window_size.w = (float)data.window_size.w;
    window_size.h = (float)data.window_size.h;
    SDL_RenderTexture(renderer, background_texture, NULL, &window_size);
}

void drawColumn(const GameFrameData data)
{
    SDL_RenderTexture(renderer, column_texture, NULL, &data.columnTop);
    SDL_RenderTexture(renderer, column_texture, NULL, &data.columnBottom);
}

void drawBird(const GameFrameData data)
{
    if ((frame % 2000) <= 1000) {
        SDL_RenderTexture(renderer, bird_texture, NULL, &data.birdRect);
    }
    else if((frame % 2000) > 1000) {
        SDL_RenderTexture(renderer, bird1_texture, NULL, &data.birdRect);
    }
}

void drawRectFocus(int rect_focus)
{
    SDL_SetRenderDrawColor(renderer, 255, 60, 60, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRectChooseUp;
    menuRectChooseUp.x = MENURECT_LEFT_MARGIN - 5;
    menuRectChooseUp.y = 90.0f * rect_focus - 5;
    menuRectChooseUp.w = MENURECT_WIDTH + 10;
    menuRectChooseUp.h = MENURECT_HEIGHT + 10;
    SDL_RenderFillRect(renderer, &menuRectChooseUp);
}

void drawGameOverRectFocus(int game_over_rect_focus)
{
    SDL_SetRenderDrawColor(renderer, 255, 60, 60, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRectChoose;
    menuRectChoose.x = MENURECT_LEFT_MARGIN - 5;
    menuRectChoose.y = 90.0f * (game_over_rect_focus + 1) - 5;
    menuRectChoose.w = MENURECT_WIDTH + 10;
    menuRectChoose.h = MENURECT_HEIGHT + 10;
    SDL_RenderFillRect(renderer, &menuRectChoose);
}

void drawMenuRects()
{
    SDL_SetRenderDrawColor(renderer, 255, 130, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRect;
    for (int i = 0; i < 3; i++)
    {
        menuRect.x = MENURECT_LEFT_MARGIN;
        menuRect.y = 90.0f + 90 * i;
        menuRect.w = MENURECT_WIDTH;
        menuRect.h = MENURECT_HEIGHT;
        SDL_RenderFillRect(renderer, &menuRect);
    }
}

void drawGameOverMenuRects()
{
    SDL_SetRenderDrawColor(renderer, 255, 130, 0, SDL_ALPHA_OPAQUE);
    SDL_FRect menuRect;
    for (int i = 1; i < 3; i++)
    {
        menuRect.x = MENURECT_LEFT_MARGIN;
        menuRect.y = 90.0f + 90 * i;
        menuRect.w = MENURECT_WIDTH;
        menuRect.h = MENURECT_HEIGHT;
        SDL_RenderFillRect(renderer, &menuRect);
    }
}

void drawScore(const GameFrameData data)
{
    char drawscore[100];
    SDL_SetRenderDrawColor(renderer, 180, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_SetRenderScale(renderer, 5.0f, 5.0f);
    snprintf(drawscore, 100, "%d", data.score);
    SDL_RenderDebugText(renderer, 60.6f, 2, drawscore);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void drawMenuText()
{
    SDL_SetRenderScale(renderer, 3.5f, 3.5f);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 60, 31, "Continue");
    SDL_RenderDebugText(renderer, 64, 57, "Restart");
    SDL_RenderDebugText(renderer, 76, 82, "Exit");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void drawGameOverMenuText()
{
    SDL_SetRenderScale(renderer, 6.0f, 6.0f);
    SDL_SetRenderDrawColor(renderer, 255, 0, 70, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 18, 17, "Game Over");
    SDL_SetRenderScale(renderer, 3.5f, 3.5f);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 64, 57, "Restart");
    SDL_RenderDebugText(renderer, 76, 82, "Exit");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void processBird(const GameFrameData data)
{
    drawBird(data);
}

void processColumn(const GameFrameData data)
{
    drawColumn(data);
}

void drawMenu(const GameFrameData data)
{
    if (data.pause && data.game_over == false)
    {
        drawRectFocus(data.pause_focus);
        drawMenuRects();
        drawMenuText();
    }
}

void drawGameOverMenu(const GameFrameData data)
{
    if (data.game_over)
    {
        drawGameOverRectFocus(data.game_over_focus);
        drawGameOverMenuRects();
        drawGameOverMenuText();
    }
}

void gameRender(const GameFrameData data)
{
    drawBackground(data);

    processBird(data);

    processColumn(data);

    drawMenu(data);

    drawGameOverMenu(data);
    
    drawScore(data);

    if (data.pause == false) {
        frame++;
    }

    SDL_RenderPresent(renderer);
}