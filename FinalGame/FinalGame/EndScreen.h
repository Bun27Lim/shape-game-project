#ifndef END_H
#define END_H

#include "GameObject.h"
#include "TextObject.h"

class EndScreen : public GameObject {

public:

	EndScreen();
	void es_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);
	void render_blank(SDL_Renderer* ren);
	TextObject* press_tab;
	TextObject* txt_score_lb;
	TextObject* txt_round_score;
	TextObject* txt_round_over;

private:

	SDL_Color textColor;
};



#endif