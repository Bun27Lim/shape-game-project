#pragma once
#include "GameEngine.h"

class PlayerShape {

	public:
		PlayerShape(const char* textureFile, int initX, int initY);
		~PlayerShape();

		void HandleEvents();
		void Update();
		void Render();

	private:
		int xPos, yPos;
		int xVel, yVel;

		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;

		//ADD STATES
};