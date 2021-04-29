#include "GameObject.h"

GameObject::GameObject() {
	//obj_graphic = NULL;

	x_pos = 0;
	y_pos = 0;
	x_vel = y_vel = width = height = 0;
	
	obj_rect.x = 0;
	obj_rect.y = 0;
	obj_rect.h = 0;
	obj_rect.w = 0;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = 0;
	src_rect.h = 0;

	accel_x = 0;
	accel_y = 0;
	angle = 0;

	reset_x = 0;
	reset_y = 0;

	texture = nullptr;

	thing_this = 0;

}

GameObject::~GameObject()
{}

//********************
// Initialize Object *
//********************
void GameObject::obj_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int start_w, int start_h, double start_angle) {
	
	int obj_size = 64;
	reset_x = start_x;
	reset_y = start_y;
	x_pos = start_x;
	y_pos = start_y;
	width = start_w;
	height = start_h;
	angle = start_angle;

	obj_rect.x = start_x;
	obj_rect.y = start_y;
	obj_rect.h = obj_size;
	obj_rect.w = obj_size;

	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.w = height;
	src_rect.h = width;

	texture = TextureManager::LoadTexture(graphic, ren);

	obj_update();
}

//****************
// Update Object *
//****************
void GameObject::obj_update()
{	

	x_vel += accel_x;
	y_vel += accel_y;

	if (x_vel > MAX_VEL)
		x_vel = MAX_VEL;
	
	if (x_vel < MAX_VEL * -1.0)
		x_vel = MAX_VEL * -1.0;


	if (y_vel > MAX_VEL)
		y_vel = MAX_VEL;

	if (y_vel < MAX_VEL * -1.0)
		y_vel = MAX_VEL * -1.0;

	if (x_pos + x_vel < 0) {
		x_pos = 0;
	}
	else if (x_pos + x_vel + obj_rect.w > SCREEN_WIDTH) {
		x_pos = SCREEN_WIDTH - obj_rect.w;
	}
	else {
		x_pos += x_vel;
	}

	if (y_pos + y_vel < 0) {
		y_pos = 0;
	}
	else if (y_pos + y_vel + obj_rect.h > SCREEN_HEIGHT) {
		y_pos = SCREEN_HEIGHT - obj_rect.h;
	}
	else {
		y_pos += y_vel;
	}


	//Check if position is at the bounds bounce
	if (x_pos <= 0) {
		x_vel *= -1.0;
	}
	if (x_pos + obj_rect.w >= SCREEN_WIDTH) {
		x_vel *= -1.0;
	}
	if (y_pos <= 0) {
		y_vel *= -1.0;
	}
	if (y_pos + obj_rect.h >= SCREEN_HEIGHT) {
		y_vel *= -1.0;
	}


	obj_rect.x = x_pos;
	obj_rect.y = y_pos;
}

//getters and setters
// 
double GameObject::obj_get_x_vel()
{
	return x_vel;
}

void GameObject::obj_set_x_vel(double x_vel_in)
{
	x_vel = x_vel_in;
}

double GameObject::obj_get_y_vel()
{
	return y_vel;
}

void GameObject::obj_set_y_vel(double y_vel_in)
{
	y_vel = y_vel_in;
}

int GameObject::obj_get_x_pos()
{
	return obj_rect.x;
}

int GameObject::obj_get_y_pos()
{
	return obj_rect.y;
}

void GameObject::obj_set_x_pos(int x_pos_in)
{
	x_pos = x_pos_in;
}
void GameObject::obj_set_y_pos(int y_pos_in)
{
	y_pos = y_pos_in;

	if (y_pos < 64) { y_pos += 64; }
}

int GameObject::obj_get_h()
{
	return obj_rect.h;
}

int GameObject::obj_get_w()
{
	return obj_rect.w;
}

int GameObject::obj_get_reset_x()
{
	return reset_x;
}

int GameObject::obj_get_reset_y()
{
	return reset_y;
}

double GameObject::obj_get_angle()
{
	return angle;
}

void GameObject::obj_set_angle(double angle_in)
{
	angle = angle_in;
}

void GameObject::obj_set_accel_x(double a)
{
	accel_x = a;
}

void GameObject::obj_set_accel_y(double a)
{
	accel_y = a;
}

void GameObject::obj_set_rand_pos()
{
	srand(time(NULL));
	x_pos = rand() % (SCREEN_WIDTH - 2* obj_rect.w) + obj_rect.w;
	y_pos = rand() % (SCREEN_HEIGHT - 2* obj_rect.h) + obj_rect.h;
	angle = (rand() % 180 - 90.0);

	std::cout << "x, y: " << x_pos << ", " << y_pos << std::endl;
}

//**************************
// Render Object to screen *
//**************************
void GameObject::obj_render(SDL_Renderer* ren)
{	
	TextureManager::Render(ren, texture, src_rect, obj_rect);
}

void GameObject::obj_renderEx(SDL_Renderer* ren)
{
	TextureManager::RenderEx(ren, texture, src_rect, obj_rect, angle, SDL_FLIP_NONE);
}

//*****************
// Destroy Object *
//*****************
void GameObject::obj_quit()
{
	SDL_DestroyTexture(texture);
}
