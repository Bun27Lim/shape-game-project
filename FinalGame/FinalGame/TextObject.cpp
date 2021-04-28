#include "TextObject.h"

TextObject::TextObject()
{
	obj_color = {0,0,0};

	obj_rect.x = 0;
	obj_rect.y = 0;
	obj_rect.w = 0;
	obj_rect.h = 0;

	x_pos = y_pos = 0;
	obj_renderer = NULL;
	obj_font = NULL;
	texture = NULL;
}

TextObject::~TextObject()
{
}

void TextObject::obj_init(const char* ttf_file, SDL_Renderer* ren, int start_x, int start_y, SDL_Color start_color, int size)
{
	
	obj_font = TTF_OpenFont(ttf_file, size);
	//obj_font = TTF_OpenFont("./images/Daniel_Light.ttf", 30);
	if (!obj_font) {
		std::cout << "Font did not load" << std::endl;
	}

	x_pos = start_x;
	y_pos = start_y;

	obj_rect.x = x_pos;
	obj_rect.y = y_pos;

	obj_color = start_color;
}

void TextObject::obj_update(const char* charString, SDL_Renderer* ren)
{
	SDL_Surface* text_surface;

	if (!(text_surface = TTF_RenderText_Solid(obj_font, charString, obj_color))) {
		std::cout << "error font" << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(ren, text_surface);
	SDL_FreeSurface(text_surface);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	//std::cout << "New String: " << charString << " Width: " << w << " Height: " << h << std::endl;

	obj_rect.w = w;
	obj_rect.h = h;
	obj_rect.x = x_pos - (w / 2);
	obj_rect.y = y_pos - (h / 2);
}

void TextObject::obj_render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, texture, NULL, &obj_rect);
}

void TextObject::obj_quit() {
	SDL_DestroyTexture(texture);
}