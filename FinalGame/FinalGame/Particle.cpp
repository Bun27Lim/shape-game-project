#include "Particle.h"

Particle::Particle()
{
	obj_rect.x = 0;
	obj_rect.y = 0;
	obj_rect.w = 0;
	obj_rect.h = 0;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = 0;
	src_rect.h = 0;

	lifetime = 0;
}

Particle::~Particle()
{
}

//State setter
void Particle::obj_set_state(int st_in) {
	state = st_in;
}

//Initializes particles
void Particle::obj_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height)
{
	int sz = 20;

	x_pos = start_x;
	y_pos = start_y;

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	obj_rect.w = sz;
	obj_rect.h = sz;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = width;
	src_rect.h = height;

	texture = TextureManager::LoadTexture(graphic, ren);


	//obj_update_hit();
}

//Updates hit
void Particle::obj_update_hit()
{
	x_pos += x_vel;
	y_pos += y_vel;

	obj_rect.x = x_pos;
	obj_rect.y = y_pos;

	lifetime -= 1;
}

//Updates miss
void Particle::obj_update_miss()
{
	x_pos += x_vel;
	y_pos += y_vel;

	y_vel += 9.8 * 100.0 / 3600.0;

	if (lifetime > 0) {
		obj_rect.x = (int) x_pos;
		obj_rect.y = (int) y_pos;
		obj_rect.w = obj_rect.w - 1;
		obj_rect.h = obj_rect.h - 1;
	}
	lifetime -= 1;
}

//Renders miss
void Particle::obj_render_miss(SDL_Renderer* ren)
{
	if (lifetime > 0) {
		TextureManager::Render(ren, texture, src_rect, obj_rect);
	}
}

//Renders hit
void Particle::obj_render_hit(SDL_Renderer* ren)
{
	if (lifetime > 0) {
		SDL_SetTextureAlphaMod(texture, (int)255 * lifetime / 20.0);
		TextureManager::Render(ren, texture, src_rect, obj_rect);
	}
	else {
		SDL_SetTextureAlphaMod(texture, 255);
	}
}

//Getters and Setters
void Particle::obj_set_x_vel(float x_in)
{
	x_vel = x_in;
}

int Particle::obj_get_x_vel()
{
	return (int) x_vel;
}

void Particle::obj_set_y_vel(float y_in)
{
	y_vel = y_in;
}

int Particle::obj_get_y_vel()
{
	return (int) y_vel;
}

int Particle::obj_get_lifetime()
{
	return lifetime;
}

void Particle::obj_set_lifetime(int life_in)
{
	lifetime = life_in;
}

void Particle::obj_quit()
{
	SDL_DestroyTexture(texture);
}
