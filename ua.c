#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Rectangles", "1.0", "com.example.renderer-rectangles");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/rectangles", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_FRect rects[16];
    const Uint64 now = SDL_GetTicks();
    int i;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    for (i = 0; i < 16; i++) {
        const float w = 20.0f;
        const float h = 100.0f;
        rects[i].x = i * 20.0f + 120;
        rects[i].y = 10 * sin(0.1 * (now / 30) + i) + 90;
        rects[i].w = w;
        rects[i].h = h;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);  /* BLUE, full alpha */
    SDL_RenderFillRects(renderer, rects, SDL_arraysize(rects));

    for (i = 0; i < 16; i++) {
        const float w = 20.0f;
        const float h = 100.0f;
        rects[i].x = i * 20.0f + 120;
        rects[i].y = 10 * sin(0.1 * (now / 30) + i) + 190;
        rects[i].w = w;
        rects[i].h = h;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);  /* YELLOW, full alpha */
    SDL_RenderFillRects(renderer, rects, SDL_arraysize(rects));

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}