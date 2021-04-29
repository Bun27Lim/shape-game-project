#include "TitleScreen.h"

TitleScreen::TitleScreen(){
	textColor = { 0,0,0 };
	press_enter = nullptr;
}


void TitleScreen::ts_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h)
{
	x_pos = start_x;
	y_pos = start_y;
	width = start_w;
	height = start_h;

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	obj_rect.h = SCREEN_HEIGHT;
	obj_rect.w = SCREEN_WIDTH;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = width;
	src_rect.h = height;

	texture = TextureManager::LoadTexture(graphic, ren);

	press_enter = new TextObject;
	textColor = { 0, 100, 10 };
	press_enter->obj_init(textFont, ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.85, textColor, 30);
	press_enter->obj_update("Press Enter to Begin!", ren);
}