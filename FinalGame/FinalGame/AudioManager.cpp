#include "AudioManager.h"

AudioManager::AudioManager() {

    Mix_Init(MIX_INIT_MP3);

    //Initialize Mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }

}

Mix_Music* AudioManager::loadMusic(const char* file) {

    Mix_Init(MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_OGG);
 
    Mix_Music* music = Mix_LoadMUS(file);
    if (music == NULL)
    {
        std::cout << "Failed to load audio! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return music;
  
}