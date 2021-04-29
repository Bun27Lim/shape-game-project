#ifndef PAUSE_H
#define PAUSE_H

#include "GameObject.h"
#include "TextObject.h"

class PauseMenu : public GameObject {

public:

	PauseMenu();
	void pause_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);
	TextObject* pause_text;
	TextObject* pause_text2;


private:

	const char* textFont = "images/dwerneck.ttf";
	SDL_Color textColor;
};



#endif