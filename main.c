#define SDL_MAIN_USE_CALLBACKS 1
#include <stdio.h>
#include "render.h"

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

static SDL_AppResult handle_key_event_(SDL_Scancode key_code)
{
    switch (key_code)
    {
    case SDL_SCANCODE_ESCAPE:
        pause = !pause;
        menu_focus = 1;
        break;
    case SDL_SCANCODE_Q:
        return SDL_APP_SUCCESS;
    case SDL_SCANCODE_SPACE:
        if (pause && game_over == false)
        {
            return processMenu();
        }
        else if (game_over)
        {
            return processGameOverMenu();
        }
        else
        {
            return SDL_APP_CONTINUE;
        }
    case SDL_SCANCODE_UP:
        if (pause && game_over == false)
        {
            rectFocusUp();
        }
        else if (game_over)
        {
            gameOverRectFocusUp();
        }
        else
        {
            birdUp();
        }
        break;
    case SDL_SCANCODE_DOWN:
        if (pause && game_over == false)
        {
            rectFocusDown();
        }
        else if (game_over)
        {
            gameOverRectFocusDown();
        }
        else
        {
            birdDown();
        }
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

SDL_AppResult SDL_AppIterate(void *appstate)
{
    gameRender();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}