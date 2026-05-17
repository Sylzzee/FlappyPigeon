#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <SDL3/SDL.h>

typedef struct GameFrameData_struct{
    int score;
    SDL_FRect birdRect;
    SDL_FRect columnTop;
    SDL_FRect columnBottom;
    SDL_Rect window_size;
    int pause_focus;
    int game_over_focus;
    bool pause;
    bool game_over;
} GameFrameData;

GameFrameData processMath();

#endif