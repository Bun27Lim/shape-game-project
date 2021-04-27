#include "GameEngine.h"


GameEngine::GameEngine(){
	endRound = false;
	totalScore = 0;
}
GameEngine::~GameEngine(){}

void GameEngine::SDL_init(const char* title, int x, int y, int width, int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Initializing SDL " << std::endl;
		Game_Window = SDL_CreateWindow(title, x, y, width, height, 0);
		Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);

		//Initialize background
		background = new BGLayer;
		background->bg_init("images/background.png", Game_Renderer, 0, 0, 3496, 2362);

		//Initialize Player Object
		PlayerObject = new GameObject;
		PlayerObject->obj_init("images/diana.png", Game_Renderer, 30, 30, 400, 400, 0);

		//Initialize Goal Object
		srand(time(NULL));
		outline = new GameObject;
		outline->obj_init("images/diana_outline.png", Game_Renderer, rand() % (SCREEN_WIDTH - 128) + 64, rand() % (SCREEN_HEIGHT - 128) + 64, 400, 400, rand() % 180 - 90);

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
			case SDLK_RIGHT:
				PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() + 2);
				break;
			
			//Move left
			case SDLK_a:
			case SDLK_LEFT:
				PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() - 2);
				break;

			//Move up (negative y direction)
			case SDLK_w:
			case SDLK_UP:
				PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() - 2);
				break;

			//Move down (positive y direction)
			case SDLK_s:
			case SDLK_DOWN:
				PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() + 2);
				break;

			case SDLK_SPACE:
				if (event.type==SDL_KEYDOWN) {
					endRound = true;
				}
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
				if (PlayerObject->obj_get_x_vel() != 0) {
					PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() / 2);
				}
				if (PlayerObject->obj_get_y_vel() != 0) {
					PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() / 2);
				}

				break;
		}
	
}

//Update Game
void GameEngine::Update() {

	PlayerObject->obj_update();
	outline->obj_update();

	if (endRound) {
		int roundScore;
		if (Accuracy::check_collision(PlayerObject, outline)) {
			roundScore = (Accuracy::overlap_area(PlayerObject, outline))/100;
		}
		else {
			roundScore = 0;
		}
		totalScore += roundScore;
		std::cout << "Score: " << totalScore << std::endl;

		// randomize and reset player
		outline->obj_set_rand_pos();
		endRound = false;
	}

}

void GameEngine::Render() {

	SDL_RenderClear(Game_Renderer);

	background->obj_render(Game_Renderer);
	outline->obj_renderEx(Game_Renderer);
	PlayerObject->obj_render(Game_Renderer);

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