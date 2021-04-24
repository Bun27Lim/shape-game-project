#ifndef BG_H
#define BG_H

#include "GameObject.h"

class BGLayer :
    public GameObject
{
public:
    void bg_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h);

    void bg_update(int);
};
#endif

