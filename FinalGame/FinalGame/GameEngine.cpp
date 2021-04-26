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

		//Initialize Player Object
		PlayerObject.obj_init("images/diana.png", Game_Renderer, 30, 30, 400, 400);

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

	//If button press is down
	
	switch (event.key.keysym.sym) {

			//Move right
			case SDLK_d:
				PlayerObject.obj_set_x_vel(PlayerObject.obj_get_x_vel() + 2);
				break;
			
			//Move left
			case SDLK_a:
				PlayerObject.obj_set_x_vel(PlayerObject.obj_get_x_vel() - 2);
				break;

			//Move up (negative y direction)
			case SDLK_w:
				PlayerObject.obj_set_y_vel(PlayerObject.obj_get_y_vel() - 2);
				break;

			//Move down (positive y direction)
			case SDLK_s:
				PlayerObject.obj_set_y_vel(PlayerObject.obj_get_y_vel() + 2);
				break;

			default:
				//Slowly (sliding effect) reset y and x velocity back to 0;
				/*if (PlayerObject.obj_get_x_vel() > 0) {
					PlayerObject.obj_set_x_vel(PlayerObject.obj_get_x_vel() - 1);
				}
				if (PlayerObject.obj_get_x_vel() < 0) {
					PlayerObject.obj_set_x_vel(PlayerObject.obj_get_x_vel() + 1);
				}
				if (PlayerObject.obj_get_y_vel() > 0) {
					PlayerObject.obj_set_y_vel(PlayerObject.obj_get_y_vel() - 1);
				}
				if (PlayerObject.obj_get_y_vel() < 0) {
					PlayerObject.obj_set_y_vel(PlayerObject.obj_get_y_vel() + 1);
				}*/
				if (PlayerObject.obj_get_x_vel() != 0) {
					PlayerObject.obj_set_x_vel(PlayerObject.obj_get_x_vel() / 2);
				}
				if (PlayerObject.obj_get_y_vel() != 0) {
					PlayerObject.obj_set_y_vel(PlayerObject.obj_get_y_vel() / 2);
				}

				break;
		}
	
}

//Update Game
void GameEngine::Update() {

	PlayerObject.obj_update();

}

void GameEngine::Render() {

	SDL_RenderClear(Game_Renderer);

	PlayerObject.obj_render(Game_Renderer);

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