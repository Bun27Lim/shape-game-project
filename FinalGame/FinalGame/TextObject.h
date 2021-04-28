#ifndef TEXT_H
#define TEXT_H

#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

class TextObject
{
public:
	TextObject();
	~TextObject();

	void obj_init(const char* ttf_file, SDL_Renderer* ren, int start_x, int start_y, SDL_Color start_color, int size);
	void obj_update(const char* charString, SDL_Renderer* ren);
	void obj_render(SDL_Renderer* ren);

	void obj_quit();

private:
	SDL_Rect obj_rect;
	SDL_Color obj_color;
	SDL_Renderer* obj_renderer;
	SDL_Texture* texture;
	TTF_Font* obj_font;

	int x_pos, y_pos;
};
#endif

