#include "SDL.h"

#include "GameEngine.h"




int main(int argc, char* argv[]) {

	//Framerate setting variables
	Uint32 frameStart;
	int frameTime;

	//Creates game engine and launches game
	GameEngine* my_game = new GameEngine();
	my_game->SDL_init("Polypals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//Standard game loop
	while (my_game->isRunning()) {

		//Begins framerate
		frameStart = SDL_GetTicks();

		//Major game loop events
		my_game->HandleEvents();
		my_game->Update();
		my_game->Render();

		//How much time it takes to get frame to frame in milliseconds
		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	//Cleans up after close
	my_game->Clean();

	return 0;
}