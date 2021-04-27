#ifndef PARTICLE_H
#define PARTICLE_H

#include "TextureManager.h"

class Particle
{
public:
	Particle();
	~Particle();

	void obj_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height);
	void obj_update_hit();
	void obj_update_miss();
	void obj_render_hit(SDL_Renderer* ren);
	void obj_render_miss(SDL_Renderer* ren);

	void obj_set_x_vel(float x_in);
	int obj_get_x_vel();
	void obj_set_y_vel(float y_in);
	int obj_get_y_vel();
	int obj_get_lifetime();
	void obj_set_lifetime(int life_in);
	void obj_set_state(int);

	void obj_quit();


private:
	SDL_Texture* texture;
	SDL_Rect obj_rect;
	SDL_Rect src_rect;

	float x_pos, y_pos;
	float x_vel, y_vel;

	int width, height;
	int state;
	int lifetime;

};
#endif

