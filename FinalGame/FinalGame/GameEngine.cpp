#include "GameEngine.h"


GameEngine::GameEngine(){
	totalScore = 0;
	timeScore = 1000;
	textColor = { 0,0,0 };

	txtScore = nullptr;
	Game_Renderer = nullptr;
	Game_Window = nullptr;
	PlayerObject = nullptr;
	background = nullptr;
	start_screen = nullptr;
	end_screen = nullptr;
	pause_menu = nullptr;
	outline = nullptr;
	pe = nullptr;
	text = nullptr;
	titleMusic = nullptr;

	endRound = false;
	Running = false;
	isPause = false;
	onEnd = false;
	onTitle = true;
	isSound = true;
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
		const char* textFont = "images/dwerneck.ttf";

		//Initialize Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}

		//Initialize Title Screen;
		start_screen = new TitleScreen;
		start_screen->ts_init("images/titlescreen.png", Game_Renderer, 0, 0, 640, 480);

		//Initialize Pause Screen;
		pause_menu = new PauseMenu;
		pause_menu->pause_init("images/background.png", Game_Renderer, 0, 0, 3496, 2362);

		//Initialize End Screen
		end_screen = new EndScreen;
		end_screen->es_init("images/endscreen.png", Game_Renderer, SCREEN_WIDTH * 0.2, SCREEN_WIDTH * 0.13, 640, 480);

		//Initialize background
		background = new BGLayer;
		background->bg_init("images/background.png", Game_Renderer, 0, 0, 3496, 2362);

		//Initialize Audio
		titleMusic = AudioManager::loadMusic("audio/ben.mp3");
		//Play the music
		Mix_PlayMusic(titleMusic, -1);
		Mix_VolumeMusic(16);

   
		//Initialize player and matching outline
		PlayerObject = new GameObject;
		outline = new GameObject;
		RandomizePlayer();

		//Create ParticleEmitter
		pe = new ParticleEmitter;

		//Create Text
		text = new TextObject;
		textColor = { 0, 0, 0 };
		text->obj_init(textFont, Game_Renderer, SCREEN_WIDTH / 2, 30, textColor, 24);
		text->obj_update("time:", Game_Renderer);
		
		txtScore = new TextObject;
		txtScore->obj_init(textFont, Game_Renderer, SCREEN_WIDTH / 2, 55, textColor, 26);
		txtScore->obj_update("1000", Game_Renderer);

		
		//Check to see if game running or quit
		Running = true;

	}
	//Error message
	else {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		Running = false;
	}

}

//Handle Events
void GameEngine::HandleEvents() {


	//Quit Game
	SDL_Event event;
	//Handle events on queue
	while (SDL_PollEvent(&event) != 0)
	{
		//User requests quit
		if (event.type == SDL_QUIT)
		{
			Running = false;
		}
	}

	//If Game is not pause handle movement
	if (!isPause && !onTitle && !onEnd)
		HandleMovement();

	switch (event.key.keysym.sym) {
			//Round reset (restarts current round; does not create new one)
		case SDLK_1:
			if (onTitle) {
				if (Mix_PlayingMusic() == 0)
				{
					//Play the music
					isSound = true;
					Mix_PlayMusic(titleMusic, -1);
				}
				//If music is being played
				else
				{
					//If the music is paused
					if (Mix_PausedMusic() == 1)
					{
						//Resume the music
						isSound = true;
						Mix_ResumeMusic();
					}
					//If the music is playing
					else
					{
						//Pause the music
						isSound = false;
						Mix_PauseMusic();
					}
				}
			}
			break;

			//Reset the current round
		case SDLK_r:
			if (!(onTitle || isPause)) {
				ResetRound(0);
				if (onEnd)
					onEnd = false;
			}
			break;

			//End current round
		case SDLK_SPACE:
			if (!(onTitle || onEnd || isPause)) {
				endRound = true;
			}
			break;

			//Start game from title screen
		case SDLK_RETURN:
			if (onTitle)
				ResetRound(1);
				onTitle = false;
			if (isPause)
				isPause = false;
			if (onEnd)
				onEnd = false;
			break;

			//Start new game from end screen
		case SDLK_TAB:
			if (onEnd) {
				onEnd = false;
				ResetRound(1);
				break;

			//Pause game
		case SDLK_ESCAPE:
			if (event.type == SDL_KEYDOWN) {
				if (!onTitle && !onEnd && !isPause) {
					isPause = true;
				}
				else if (!onTitle && isPause) {
					onTitle = true;
					if(isSound)
						Mix_ResumeMusic();
				}
				else if (onEnd) {
					onTitle = true;
					onEnd = false;
				}
				else if (onTitle) {
					Running = false;
				}
				else {
					isPause = false;
				}
			}
		default:
			if (!onTitle)
			{
				//Pause the music
				Mix_PauseMusic();
			}
			if (onTitle && isSound) {
				Mix_ResumeMusic();
			}

			break;
			}
		}
	
}

//Update Game
void GameEngine::Update() {

	//Update particle emitter if it has been initialized
	if (pe->pe_started) {
		pe->pe_update();
	}

	//Checks to make sure round is in progress
	if (!(onTitle || onEnd || isPause)) {
		PlayerObject->obj_update();
		outline->obj_update();

		timeScore -= 1;
		if (timeScore < 0) timeScore = 0;

		//Calculates score at end of round
		if (endRound) {
			onEnd = true;

			double roundScore;
			if (Accuracy::check_collision(PlayerObject, outline)) {
				roundScore = (Accuracy::overlap_area(PlayerObject, outline)) / 4000.0;
				std::cout << "score multiplier: " << roundScore << std::endl;
				pe->pe_init("./images/jeff.png", Game_Renderer, PlayerObject->obj_get_x_pos(), PlayerObject->obj_get_y_pos(), 400, 400, 1); //if collided
			}
			else {
				roundScore = 0;
				pe->pe_init("./images/diana.png", Game_Renderer, PlayerObject->obj_get_x_pos(), PlayerObject->obj_get_y_pos(), 400, 400, 0);	//not collided
			}

			totalScore = timeScore * roundScore;
			std::cout << "round score: " << totalScore << std::endl;

			endRound = false;

			//Updates score for end screen
			std::string s = std::to_string(totalScore);
			char const* charScore = s.c_str();
			end_screen->txt_round_score->obj_update(charScore, Game_Renderer);
		}
		std::string s = std::to_string(timeScore);	
		char const* charScore = s.c_str();
		txtScore->obj_update(charScore, Game_Renderer);
	}
}

//Texture renderer
void GameEngine::Render() {

	SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255); //white screen
	SDL_RenderClear(Game_Renderer);

	//Start Screen
	if (onTitle) {
		start_screen->obj_render(Game_Renderer);
		start_screen->press_enter->obj_render(Game_Renderer);
	}
	//Pause Menu
	else if (isPause) {
		pause_menu->obj_render(Game_Renderer);
		text->obj_render(Game_Renderer);
		txtScore->obj_render(Game_Renderer);
		pause_menu->pause_text->obj_render(Game_Renderer);
		pause_menu->pause_text2->obj_render(Game_Renderer);
	}
	//Regular Game
	else {

		background->obj_render(Game_Renderer);
		text->obj_render(Game_Renderer);
		txtScore->obj_render(Game_Renderer);
		outline->obj_renderEx(Game_Renderer);
		PlayerObject->obj_renderEx(Game_Renderer);

		if (onEnd) {
			end_screen->render_blank(Game_Renderer);
			end_screen->txt_round_over->obj_render(Game_Renderer);
			end_screen->press_tab->obj_render(Game_Renderer);
			end_screen->txt_score_lb->obj_render(Game_Renderer);
			end_screen->txt_round_score->obj_render(Game_Renderer);
		}
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
	end_screen->obj_quit();
	outline->obj_quit();
	//pe->pe_quit();
	
	SDL_DestroyWindow(Game_Window);
	SDL_DestroyRenderer(Game_Renderer);

	Mix_FreeMusic(titleMusic);
	titleMusic = NULL;
	
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

//Check to see if game is running
bool GameEngine::isRunning() {
	return Running;
}

//Restarts round to original starting position
void GameEngine::ResetRound(int newIn) {
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

	//Reset Angle
	PlayerObject->obj_set_angle(0);

	//Reset score and timer
	totalScore = 0;
	timeScore = 1000;

	if (newIn == 1) {
		//If new game is started, make new player and outline
		RandomizePlayer();
		outline->obj_set_rand_pos();
		outline->obj_set_x_pos(outline->obj_get_reset_x());
		outline->obj_set_y_pos(outline->obj_get_reset_y());
		outline->obj_set_angle(outline->obj_get_reset_angle());
	}

}

//Handle key states
void GameEngine::HandleMovement() {

	// Go right +x direction
	if ( keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
		PlayerObject->obj_set_accel_x(PlayerObject->ACCEL);
	}
	// Go left -x direction
	if ( keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
		PlayerObject->obj_set_accel_x(PlayerObject->ACCEL * (-1.0));
	}
	// Go up -y direction
	if ( keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP]) { 
		PlayerObject->obj_set_accel_y(PlayerObject->ACCEL * (-1.0));
	}
	// Go down +y direction
	if ( keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN]) { 
		PlayerObject->obj_set_accel_y(PlayerObject->ACCEL);
	}

	// If left and right keys are up, decelerate x acceleration
	if (!keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT] && !keyState[SDL_SCANCODE_A] && !keyState[SDL_SCANCODE_D]) {
		PlayerObject->obj_set_accel_x(0);

		if (PlayerObject->obj_get_x_vel() < 0) {
			PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() + 0.2);
		}
		if (PlayerObject->obj_get_x_vel() > 0) {
			PlayerObject->obj_set_x_vel(PlayerObject->obj_get_x_vel() - 0.2);
		}
		if (PlayerObject->obj_get_x_vel() < 0.05 || PlayerObject->obj_get_x_vel() > -0.05) {
			PlayerObject->obj_set_x_vel(0);
		}

	}

	//If up and down keys are up, decelerate y acceleration
	if (!keyState[SDL_SCANCODE_UP] && !keyState[SDL_SCANCODE_DOWN] && !keyState[SDL_SCANCODE_W] && !keyState[SDL_SCANCODE_S]) {
		PlayerObject->obj_set_accel_y(0);

		if (PlayerObject->obj_get_y_vel() < 0) {
			PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() + 0.2);
		}
		if (PlayerObject->obj_get_y_vel() > 0) {
			PlayerObject->obj_set_y_vel(PlayerObject->obj_get_y_vel() - 0.2);
		}
		if (PlayerObject->obj_get_y_vel() < 0.05 || PlayerObject->obj_get_y_vel() > -0.05) {
			PlayerObject->obj_set_y_vel(0);
		}
	}
	
	// Rotate Counter-Clockwise
	if (keyState[SDL_SCANCODE_Q] || keyState[SDL_SCANCODE_V]) {
		PlayerObject->obj_set_angle_vel(PlayerObject->obj_get_angle_vel() - 2);
	}
	// Rotate Clockwise
	else if (keyState[SDL_SCANCODE_E] || keyState[SDL_SCANCODE_B]) {
		PlayerObject->obj_set_angle_vel(PlayerObject->obj_get_angle_vel() + 2);
	}
	else {
		if (PlayerObject->obj_get_angle_vel() > 0) {
			PlayerObject->obj_set_angle_vel(PlayerObject->obj_get_angle_vel() - 1);
		}
		if (PlayerObject->obj_get_angle_vel() < 0) {
			PlayerObject->obj_set_angle_vel(PlayerObject->obj_get_angle_vel() + 1);
		}
	}

}

void GameEngine::RandomizePlayer() {

	srand((unsigned int)time(NULL));
	
	int pal = rand() % 5;
	int sz = 400;
	int rand_w = rand() % (SCREEN_WIDTH - 256) + 128;
	int rand_h = rand() % (SCREEN_HEIGHT - 256) + 128;
	double rand_agl = rand() % 180 - 90.0;

	//Switch statement for selecting both character and cooresponding outline
	switch (pal)
	{
	case 0:
		PlayerObject->obj_init("images/jeff.png", Game_Renderer, 30, SCREEN_HEIGHT*0.8, sz, sz, 0);
		outline->obj_init("images/jeff_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
		break;

	case 1:
		PlayerObject->obj_init("images/travis.png", Game_Renderer, 30, SCREEN_HEIGHT * 0.8, sz, sz, 0);
		outline->obj_init("images/travis_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
		break;

	case 2:
		PlayerObject->obj_init("images/diana.png", Game_Renderer, 30, SCREEN_HEIGHT * 0.8, sz, sz, 0);
		outline->obj_init("images/diana_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
		break;

	case 3:
		PlayerObject->obj_init("images/katie.png", Game_Renderer, 30, SCREEN_HEIGHT * 0.8, sz, sz, 0);
		outline->obj_init("images/katie_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
		break;

	case 4:
		PlayerObject->obj_init("images/luna.png", Game_Renderer, 30, SCREEN_HEIGHT * 0.8, sz, sz, 0);
		outline->obj_init("images/luna_outline.png", Game_Renderer, rand_w, rand_h, sz, sz, rand_agl);
		break;

	default:
		break;
	}
}