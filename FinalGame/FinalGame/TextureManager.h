#pragma once

#include "GameEngine.h"


class TextureManager {

	public:
		static SDL_Texture* LoadTexture(const char* file);
		static void Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

	private:
};