#include "PauseMenu.h"

#include "TitleScreen.h"

PauseMenu::PauseMenu(){
	textColor = { 0,0,0 };
	pause_text = NULL;
	pause_text2 = NULL;
}

//Initializes pause
void PauseMenu::pause_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h)
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

	const char* textFont = "images/dwerneck.ttf";

	pause_text = new TextObject;
	textColor = { 10, 100, 0 };
	pause_text->obj_init(textFont, ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.45, textColor, 30);
	pause_text->obj_update("Game is PAUSED", ren);

	pause_text2 = new TextObject;
	textColor = { 10, 100, 0 };
	pause_text2->obj_init(textFont, ren, SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.55, textColor, 30);
	pause_text2->obj_update("Press ENTER to continue", ren);

}