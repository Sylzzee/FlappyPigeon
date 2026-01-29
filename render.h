#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_surface.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static char background_path[] = "background.bmp";
static char bird_path[] = "Bird.bmp";
static char column_path[] = "column.bmp";
static SDL_Texture *background_texture = NULL;
static SDL_Texture *bird_texture = NULL;
static SDL_Texture *column_texture = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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