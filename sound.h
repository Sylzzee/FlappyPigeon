#ifndef SOUND_H
#define SOUND_H

#include <SDL3/SDL.h>

void DestroyWAV(SDL_AudioStream *stream, Uint8 *wav_data);

typedef struct GameSoundData_struct
{
    SDL_AudioStream *stream; 
    Uint8 *wav_data;
    SDL_AppResult ProgramState;
} GameSoundData;

GameSoundData GameSound_Init();

//GameSoundData processSound();

#endif