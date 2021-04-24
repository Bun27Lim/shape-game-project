#pragma once
#include "SDL.h"

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

		static SDL_Renderer* Game_Renderer;


	private:
		SDL_Window* Game_Window;

		bool Running;
};
