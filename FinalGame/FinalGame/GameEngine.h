#ifndef GE_H
#define GE_H

#include "screenInfo.h"
#include "GameObject.h"
#include "BGLayer.h"
#include "TitleScreen.h"
#include "PauseMenu.h"
#include "EndScreen.h"
#include "Accuracy.h"
#include "ParticleEmitter.h"
#include "TextObject.h"
#include "AudioManager.h"
#include <cstdlib>
#include <time.h>

class GameEngine {
                                                 
	public:
		GameEngine();
		~GameEngine();

		void SDL_init(const char* title, int x, int y, int width, int height);
		void HandleEvents();
		void Update();
		void Render();
		void Clean();

		bool isRunning();

		SDL_Renderer* Game_Renderer;


	private:
		void HandleMovement();
		void RandomizePlayer();
		void ResetRound(int);

		SDL_Window* Game_Window;

		GameObject* PlayerObject;
		GameObject* outline;
		BGLayer* background;
		TitleScreen* start_screen;
		PauseMenu* pause_menu;
		EndScreen* end_screen;
		ParticleEmitter* pe;
		SDL_Color textColor;

		// text labels
		TextObject* text;
		TextObject* txtScore;

		//Audio Stuff
		Mix_Music* titleMusic;

		const Uint8* keyState = SDL_GetKeyboardState(NULL);

		int totalScore;
		int timeScore;
		bool Running;
		bool endRound;
		bool onTitle;
		bool onEnd;
		bool isPause;
		bool isSound;
};
#endif