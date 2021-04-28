#ifndef TITLE_H
#define TITLE_H

#include "GameObject.h"

class TitleScreen : public GameObject {

public:

	void ts_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);


private:

};



#endif