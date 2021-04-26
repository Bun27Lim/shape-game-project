#include "GameEngine.h"
#include <iostream>

GameObject PlayerObject;

GameEngine::GameEngine(){}
GameEngine::~GameEngine(){}

void GameEngine::SDL_init(const char* title, int x, int y, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Initializing SDL " << std::endl;
		Game_Window = SDL_CreateWindow(title, x, y, width, height, 0);
		Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);

		//Create Player Object


		//Testing white screen
		SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255);

		Running = true;




	}
	else {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		Running = false;
	}

}

//Handle Events
void GameEngine::HandleEvents() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			Running = false;
			break;
	
		default:
			break;
	}

}

//Update Game
void GameEngine::Update() {

}

void GameEngine::Render() {

	SDL_RenderClear(Game_Renderer);
	//Render Copy here
	
	SDL_RenderPresent(Game_Renderer);
}

//Clean when game is finished
void GameEngine::Clean() {
	
	SDL_DestroyWindow(Game_Window);
	SDL_DestroyRenderer(Game_Renderer);
	SDL_Quit();
}

bool GameEngine::isRunning() {
	return Running;
}