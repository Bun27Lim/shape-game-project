#ifndef OBJECT_H
#define OBJECT_H

#include "TextureManager.h"

//#include "Sprite.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void obj_init(const char*, SDL_Renderer*, int, int, int, int);
	void obj_update();
	
	void obj_render(SDL_Renderer*);
	void obj_quit();

	int obj_get_x_vel();
	void obj_set_x_vel(int);
	int obj_get_y_vel();
	void obj_set_y_vel(int);
	int obj_get_x_pos();
	int obj_get_y_pos();
	void obj_set_x_pos(int);
	void obj_set_y_pos(int);
	int obj_get_h();
	int obj_get_w();


protected:
	//Sprite* obj_sprite;
	TextureManager* image;

	SDL_Texture* texture;

	SDL_Rect obj_rect;
	SDL_Rect src_rect;	

	int width, height;
	int x_pos, x_vel;
	int y_pos, y_vel;

private:


};
#endif

