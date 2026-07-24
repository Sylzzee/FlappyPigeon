#ifndef SOUND_H
#define SOUND_H

#include <SDL3/SDL.h>

typedef struct GameSoundData_struct
{
    SDL_AudioStream *stream; 
    Uint8 *wav_data;
    SDL_AppResult ProgramState;
} GameSoundData;

GameSoundData GameSound_Init();

void DestroyWAV(SDL_AudioStream *stream, Uint8 *wav_data);

void FlappingSound();

//GameSoundData processSound();

#endif