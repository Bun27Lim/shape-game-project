#ifndef AUDIO_H
#define AUDIO_H

#include "SDL_mixer.h"
#include <iostream>

class AudioManager {

public:
	AudioManager();
	
	static Mix_Music* loadMusic(const char* file);


private:


};


#endif
