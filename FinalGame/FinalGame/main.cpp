#include "SDL.h"

#include "GameEngine.h"




int main(int argc, char* argv[]) {

	Uint32 frameStart;
	int frameTime;

	GameEngine* my_game = new GameEngine();
	my_game->SDL_init("Polypals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	while (my_game->isRunning()) {

		frameStart = SDL_GetTicks();

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

	my_game->Clean();

	return 0;
}