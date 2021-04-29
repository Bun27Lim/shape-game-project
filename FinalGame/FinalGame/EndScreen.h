#ifndef END_H
#define END_H

#include "GameObject.h"
#include "TextObject.h"

class EndScreen : public GameObject {

public:

	EndScreen();
	void es_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);
	TextObject* press_tab;

private:

	const char* textFont = "images/dwerneck.ttf";

	SDL_Color textColor;
};



#endif