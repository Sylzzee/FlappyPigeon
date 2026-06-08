#include "sound.h"
#include <SDL3/SDL.h>

GameSoundData GameSound_Init()
{
    GameSoundData data_sound;

    data_sound.stream = NULL;
    data_sound.wav_data = NULL;
    data_sound.ProgramState = SDL_APP_FAILURE;



    Uint8 *wav_data = NULL; //вказівник на скачаний аудіо-файл
    Uint32 wav_data_len = 0; //кількість байт, який займає цей аудіо-файл
    SDL_AudioSpec wav_spec; //уточнювач формату, х-стика аудіо-файлу

    if (!SDL_LoadWAV("1-02 - Moon in One's Cup.wav", &wav_spec, &wav_data, &wav_data_len)) { //загружає аудіо-файл
        SDL_Log("Couldn't initialize WAV: %s", SDL_GetError());
        return data_sound;
    }

    SDL_AudioStream *stream = SDL_OpenAudioDeviceStream( //приймач аудіо-файла
        SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, 
        &wav_spec, 
        NULL,  
        NULL
    );

    if (!stream) {
        SDL_Log("Couldn't initialize audiostream: %s", SDL_GetError());
        SDL_free(wav_data);
        return data_sound;
    }

    if (!SDL_PutAudioStreamData(stream, wav_data, wav_data_len)) { //кладемо аудіо-файл в стрім(приймач цього файла)
        SDL_Log("errrrrrrror: %s", SDL_GetError());
    }

    SDL_FlushAudioStream(stream); //конвертація wav у ТИП який може прочитати система хз
    SDL_ResumeAudioStreamDevice(stream); //анпаузить наше аудіо
    
    return data_sound;
}

void DestroyWAV(SDL_AudioStream *stream, Uint8 *wav_data) 
{
    SDL_DestroyAudioStream(stream); //знищення стріма (треба робити при закритті програми)
    SDL_free(wav_data);
} 
