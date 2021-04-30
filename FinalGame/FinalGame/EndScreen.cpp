#include "EndScreen.h"

EndScreen::EndScreen() {
	textColor = { 0,0,0 };
	press_tab = NULL;
	txt_round_score = NULL;
	txt_score_lb = NULL;
	txt_round_over = NULL;
}

//Initializes and displays end screen
void EndScreen::es_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h)
{
	x_pos = start_x;
	y_pos = start_y;
	width = start_w;
	height = start_h;

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	obj_rect.h = SCREEN_HEIGHT*0.6;
	obj_rect.w = SCREEN_WIDTH*0.6;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = width;
	src_rect.h = height;

	texture = TextureManager::LoadTexture(graphic, ren);
	const char* textFont = "images/dwerneck.ttf";
	const char* textFont2 = "images/danielbd.ttf";

	//Shows round over text
	txt_round_over = new TextObject;
	textColor = { 200, 50, 50 };
	txt_round_over->obj_init(textFont2, ren, SCREEN_WIDTH / 2, (int)SCREEN_HEIGHT * 0.3, textColor, 50);
	txt_round_over->obj_update("Round Over", ren);

	//Shows play again text
	press_tab = new TextObject;
	textColor = { 0, 150, 50 };
	press_tab->obj_init(textFont2, ren, SCREEN_WIDTH / 2, (int) SCREEN_HEIGHT * 0.7, textColor, 24);
	press_tab->obj_update("Press Tab to Play Again!", ren);

	//Displays "Your Score"
	txt_score_lb = new TextObject;
	textColor = { 0, 130, 200 };
	txt_score_lb->obj_init(textFont, ren, SCREEN_WIDTH / 2, (int)(SCREEN_HEIGHT * 0.45), textColor, 40);
	txt_score_lb->obj_update("Your Score", ren);

	//Displays score value
	txt_round_score = new TextObject;
	textColor = { 200, 200, 0 };
	txt_round_score->obj_init(textFont, ren, SCREEN_WIDTH / 2, (int)(SCREEN_HEIGHT * 0.55), textColor, 36);
	txt_round_score->obj_update("0", ren);
}

void EndScreen::render_blank(SDL_Renderer* ren)
{
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(ren, 20, 20, 20, 200);
	SDL_RenderFillRect(ren, &obj_rect);
}