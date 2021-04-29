#ifndef TITLE_H
#define TITLE_H

#include "GameObject.h"
#include "TextObject.h"

class TitleScreen : public GameObject {

public:

	TitleScreen();
	void ts_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);
	TextObject* press_enter;


private:
	
	const char* textFont = "images/dwerneck.ttf";
	SDL_Color textColor;
};



#endif