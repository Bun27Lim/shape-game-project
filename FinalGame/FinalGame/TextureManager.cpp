#include "TextureManager.h"
#include "SDL_Image.h"
SDL_Texture* TextureManager::LoadTexture(const char* file) {

	SDL_Surface* texture_surface = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameEngine::Game_Renderer, texture_surface);
	SDL_FreeSurface(texture_surface);

	return texture;
}

void TextureManager::Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(GameEngine::Game_Renderer, texture, &src, &dest);
}