#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>
#include <stdio.h>
#include <stdbool.h>
#include "render.h"

static float rect_hole = 0.5;
static float bird = 0.5;
static float column = 1;
static float pause = 0;
static bool flag = 1;
static int game_over = 0;
static float column_speed = 0.18;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define PIXELS_PER_SECOND 60
#define BIRD_LEFT_MARGIN 120
#define BIRD_RIGHT_X (BIRD_LEFT_MARGIN + BIRD_WIDTH)
#define BIRD_WIDTH 80
#define BIRD_HEIGHT 30
#define COLUMN_WIDTH 60
#define HOLE_HEIGHT 60
#define MENURECT_LEFT_MARGIN 160
#define MENURECT_WIDTH 320
#define MENURECT_HEIGHT 60
#define TEXT_SIZE 20

int addscore = 0;

static Uint64 last_time = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Rectangles", "1.0", "com.example.renderer-rectangles");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return Game_Init();
}

int add(int a, int b) {
    return a + b;
}

int addsqr(int a, int b) {
    return add(a, b) * add(a, b);
}

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

static SDL_AppResult handle_key_event_(SDL_Scancode key_code)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    switch (key_code)
    {
    case SDL_SCANCODE_ESCAPE:
        pause = !pause;
        break;
    case SDL_SCANCODE_Q:
        return SDL_APP_SUCCESS;
    case SDL_SCANCODE_UP:
        bird -= 0.1f;
        birdLimit();
        break;
    case SDL_SCANCODE_DOWN:
        bird += 0.1f;
        birdLimit();
        break;
    default:
        break;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    else if (event->type == SDL_EVENT_KEY_DOWN)
    {
        return handle_key_event_(event->key.scancode);
    }
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

float getColumnX()
{
    return column * WINDOW_WIDTH;
}

float getColumnRightX()
{
    return getColumnX() + COLUMN_WIDTH;
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

void writeMenuText(const Uint64 now)
{
    char score[100];
    SDL_SetRenderScale(renderer, 3.5f, 3.5f);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 60, 31, "Continue");
    SDL_RenderDebugText(renderer, 60, 57, "Settings");
    SDL_RenderDebugText(renderer, 76, 82, "Exit");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    const Uint64 now = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const float elapsed = ((float)(now - last_time)) / 1000.0f;

    drawBackground();

    updateColumn(elapsed);
    drawColumn();

    if (!pause)
    {
        bird += 0.1 * elapsed;
        birdLimit();
    }

    drawBird();

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

    if (pause)
    {
        drawMenuRects();
        writeMenuText(now);
    }

    drawScore();

    last_time = now;

    SDL_RenderPresent(renderer);
    if (game_over == 0)
    {
        return SDL_APP_CONTINUE;
    }
    else
    {
        return SDL_APP_SUCCESS;
    }
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}
