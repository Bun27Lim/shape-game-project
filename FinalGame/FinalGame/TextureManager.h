#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"


class TextureManager {

	public:

		static SDL_Texture* LoadTexture(const char* file, SDL_Renderer* ren);
		static void Render(SDL_Renderer* ren, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

	private:
};
#endif