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

		//Initialize TTF
		if (TTF_Init() == -1) {
			std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
			exit(2);
		}

		//Initialize Title Screen;
		start_screen = new TitleScreen;
		start_screen->ts_init("images/titlescreen.png", Game_Renderer, 0, 0, 640, 480);
		onTitle = true;

		//Create Title Text
		press_enter = new TextObject;
		textColor = { 0, 0, 0 };
		press_enter->obj_init("./images/Daniel_Light.ttf", Game_Renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.85, textColor, 36);
		press_enter->obj_update("Press Enter to Begin!", Game_Renderer);

		//Initialize background
		background = new BGLayer;
		background->bg_init("images/background.png", Game_Renderer, 0, 0, 3496, 2362);

		//Initialize Player Object
		PlayerObject = new GameObject;
    
		//Initialize Player Object Randomly
		//Initialize matching outline
		srand(time(NULL));
		PlayerObject = new GameObject;
		outline = new GameObject;
		int pal = rand() % 5;
		int sz = 400;
		int rand_w = rand() % (SCREEN_WIDTH - 128) + 64;
		int rand_h = rand() % (SCREEN_HEIGHT - 128) + 64;
		double rand_agl = rand() % 180 - 90.0;

		switch (pal)
		{
		case 0:
			PlayerObject->obj_init("images/jeff.png", Game_Renderer, 30, 30, sz, sz, 0);
			outline->obj_init("images/jeff_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
			break;
		
		case 1:
			PlayerObject->obj_init("images/travis.png", Game_Renderer, 30, 30, sz, sz, 0);
			outline->obj_init("images/travis_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
			break;

		case 2:
			PlayerObject->obj_init("images/diana.png", Game_Renderer, 30, 30, sz, sz, 0);
			outline->obj_init("images/diana_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
			break;

		case 3:
			PlayerObject->obj_init("images/katie.png", Game_Renderer, 30, 30, sz, sz, 0);
			outline->obj_init("images/katie_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
			break;

		case 4:
			PlayerObject->obj_init("images/luna.png", Game_Renderer, 30, 30, sz, sz, 0);
			outline->obj_init("images/luna_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
			break;
		
		default:
			break;
		}

		//Create ParticleEmitter
		pe = new ParticleEmitter;

		//Create Text
		text = new TextObject;
		textColor = { 0, 0, 0 };
		text->obj_init("./images/Daniel_Light.ttf", Game_Renderer, SCREEN_WIDTH / 2, 50, textColor, 36);
		text->obj_update("Score:", Game_Renderer);

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
			PlayerObject->obj_set_accel_x(PlayerObject->ACCEL);
			break;

			//Move left
		case SDLK_a:
		case SDLK_LEFT:
			PlayerObject->obj_set_accel_x(PlayerObject->ACCEL * (-1.0));
			break;

			//Move up (negative y direction)
		case SDLK_w:
		case SDLK_UP:
			PlayerObject->obj_set_accel_y(PlayerObject->ACCEL * (-1.0));
			break;

			//Move down (positive y direction)
		case SDLK_s:
		case SDLK_DOWN:
			PlayerObject->obj_set_accel_y(PlayerObject->ACCEL);
			break;

		case SDLK_r:
			GameEngine::ResetRound();
			break;

		case SDLK_SPACE:
			if (event.type == SDL_KEYDOWN) {
				endRound = true;
			}
			break;


		case SDLK_RETURN:
			if (onTitle)
				onTitle = false;
			break;

		default:
			//If left and right keys are up, decelerate x acceleration
			if (!(keyState[SDLK_a] && keyState[SDLK_LEFT] && keyState[SDLK_d] && keyState[SDLK_RIGHT])) {
				//std::cout << "decelerate X" << std::endl;
				//std::cout << PlayerObject->obj_get_x_vel() << std::endl;
				PlayerObject->obj_set_accel_x(0);
				if (PlayerObject->obj_get_x_vel() < 0) {
					//std::cout << "decelerate X" << std::endl;
					PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() + 0.25);
					//std::cout << PlayerObject->obj_get_x_vel() << std::endl;
				}
				if (PlayerObject->obj_get_x_vel() > 0) {
					PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() - 0.25);
				}
			}
			//If up and down keys are up, decelerate y acceleration
			if (!(keyState[SDLK_w] && keyState[SDLK_UP] && keyState[SDLK_s] && keyState[SDLK_DOWN])) {
				PlayerObject->obj_set_accel_y(0);
				if (PlayerObject->obj_get_y_vel() < 0) {
					//std::cout << "decelerate Y" << std::endl;
					PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() + 0.25);
				}
				if (PlayerObject->obj_get_y_vel() > 0) {
					PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() - 0.25);
				}
			}
			break;
		}
	
}

//Update Game
void GameEngine::Update() {
	if (!onTitle) {
		PlayerObject->obj_update();
		outline->obj_update();

		if (pe->pe_started) {
			pe->pe_update();
		}
		if (endRound) {
			int roundScore;
			if (Accuracy::check_collision(PlayerObject, outline)) {
				roundScore = (Accuracy::overlap_area(PlayerObject, outline)) / 100;
				pe->pe_init("./images/jeff.png", Game_Renderer, PlayerObject->obj_get_x_pos(), PlayerObject->obj_get_y_pos(), 400, 400, 1); //if collided
			}
			else {
				roundScore = 0;
				pe->pe_init("./images/diana.png", Game_Renderer, PlayerObject->obj_get_x_pos(), PlayerObject->obj_get_y_pos(), 400, 400, 0);	//not collided
			}
			totalScore += roundScore;
			std::cout << "Score: " << totalScore << std::endl;

			// randomize and reset player
			outline->obj_set_rand_pos();
			endRound = false;
			text->obj_update("Score:", Game_Renderer);
		}
	}
}

void GameEngine::Render() {

	SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255);
	SDL_RenderClear(Game_Renderer);

	if (onTitle) {
		start_screen->obj_render(Game_Renderer);
		press_enter->obj_render(Game_Renderer);
	}
	else {
		background->obj_render(Game_Renderer);
		text->obj_render(Game_Renderer);
		outline->obj_renderEx(Game_Renderer);
		PlayerObject->obj_render(Game_Renderer);
	}


	// Render particles
	if (pe->pe_started) {
		pe->pe_render(Game_Renderer);
	}

	SDL_RenderPresent(Game_Renderer);
}

//Clean when game is finished
void GameEngine::Clean() {

	PlayerObject->obj_quit();
	background->obj_quit();
	start_screen->obj_quit();
	outline->obj_quit();
	//pe->pe_quit();
	
	SDL_DestroyWindow(Game_Window);
	SDL_DestroyRenderer(Game_Renderer);
	
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool GameEngine::isRunning() {
	return Running;
}

void GameEngine::ResetRound() {
	//Reset back to starting position
	PlayerObject->obj_set_x_pos(PlayerObject->obj_get_reset_x());
	PlayerObject->obj_set_y_pos(PlayerObject->obj_get_reset_y());

	std::cout << "Starting X: " << PlayerObject->obj_get_reset_x() << std::endl;
	std::cout << "Starting Y: " << PlayerObject->obj_get_reset_y() << std::endl;
	//Reset Acceleration
	PlayerObject->obj_set_accel_x(0);
	PlayerObject->obj_set_accel_y(0);

	//Reset Velocity
	PlayerObject->obj_set_x_vel(0);
	PlayerObject->obj_set_y_vel(0);

	//Reset Timer


}