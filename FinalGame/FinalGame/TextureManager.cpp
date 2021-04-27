#include "TextureManager.h"
#include "SDL_Image.h"

SDL_Texture* TextureManager::LoadTexture(const char* file, SDL_Renderer* ren) {

	SDL_Surface* texture_surface = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, texture_surface);
	SDL_FreeSurface(texture_surface);

	return texture;
}

void TextureManager::Render(SDL_Renderer* ren, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(ren, texture, &src, &dest);
}

void TextureManager::RenderEx(SDL_Renderer* ren, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, double angle, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(ren, texture, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}
