#ifndef OBJECT_H
#define OBJECT_H

#include "screenInfo.h"
#include "TextureManager.h"

//#include "Sprite.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void obj_init(const char*, SDL_Renderer*, int, int, int, int, double);
	void obj_update();
	
	void obj_render(SDL_Renderer*);
	void obj_renderEx(SDL_Renderer*);
	void obj_quit();

	double obj_get_x_vel();
	void obj_set_x_vel(double);
	double obj_get_y_vel();
	void obj_set_y_vel(double);
	int obj_get_x_pos();
	int obj_get_y_pos();
	void obj_set_x_pos(int);
	void obj_set_y_pos(int);
	int obj_get_h();
	int obj_get_w();
	int obj_get_reset_x();
	int obj_get_reset_y();
	void obj_set_accel_x(double);
	void obj_set_accel_y(double);
	double obj_get_accel_x();

	double obj_get_angle_vel();
	void obj_set_angle_vel(double);
	double obj_get_angle();
	double obj_get_reset_angle();
	void obj_set_angle(double);

	void obj_set_rand_pos();

	static const int ACCEL = 2;
	static const int MAX_VEL = 10; 
	static const int MAX_ROT = 10;

protected:
	//Sprite* obj_sprite;
	SDL_Texture* texture;

	SDL_Rect obj_rect;
	SDL_Rect src_rect;	

	int reset_x, reset_y;
	double reset_angle;
	int width, height;
	double accel_x, accel_y;
	int x_pos, y_pos;
	double x_vel, y_vel, angle_vel;
	double angle;

private:

};
#endif

