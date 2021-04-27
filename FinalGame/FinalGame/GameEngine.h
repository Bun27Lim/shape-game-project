#ifndef GE_H
#define GE_H

#include "PlayerShape.h"
#include "GameObject.h"
#include "Accuracy.h"
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
		SDL_Window* Game_Window;

		bool Running;
};
#endif