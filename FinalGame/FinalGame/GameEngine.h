#ifndef GE_H
#define GE_H

#include "screenInfo.h"
#include "PlayerShape.h"
#include "GameObject.h"
#include "BGLayer.h"
#include "TitleScreen.h"
#include "EndScreen.h"
#include "Accuracy.h"
#include "ParticleEmitter.h"
#include "TextObject.h"
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

		void ResetRound();

		SDL_Renderer* Game_Renderer;


	private:
		SDL_Window* Game_Window;

		GameObject* PlayerObject;
		GameObject* outline;
		BGLayer* background;
		TitleScreen* start_screen;
		EndScreen* end_screen;
		ParticleEmitter* pe;
		SDL_Color textColor;
		TextObject* text;
		TextObject* press_enter;
		TextObject* press_tab;

		const Uint8* keyState = SDL_GetKeyboardState(NULL);


		int totalScore;
		bool Running;
		bool endRound;
		bool onTitle;
		bool onEnd;
		bool isPause;
};
#endif