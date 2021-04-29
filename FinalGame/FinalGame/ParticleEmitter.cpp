#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter()
{
	part_type = 0;
	pos_x = 0;
	pos_y = 0;

	pe_started = false;
}

ParticleEmitter::~ParticleEmitter()
{
}

//Emitter initialization
void ParticleEmitter::pe_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type)
{
	pe_started = true;
	srand(5);
	part_type = type;
	int max_parts = MAX_PARTS;

	if (part_type == 0) {
		max_parts = MAX_PARTS_MISS;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_set_state(part_type);

			particles[i].obj_init(graphic, ren, start_x, start_y, width, height);
			particles[i].obj_set_x_vel(3.0 - (rand() % 60) / 10.0);
			particles[i].obj_set_y_vel(0 - (rand() % 60) / 10.0);
			particles[i].obj_set_lifetime(20 + (rand() % 10));

			
		}
		
	}

	if (part_type == 1) {
		for (int i = 0; i < max_parts; i++){
			particles[i].obj_set_lifetime(15 + (rand() % 10));
			particles[i].obj_set_state(part_type);

			switch (rand() % 4) {
			case 0:
				particles[i].obj_init(graphic, ren, start_x, start_y - 17 + rand() % 34, width, height);
				particles[i].obj_set_x_vel(5.0 +  (rand() % 50) / 10.0);
				particles[i].obj_set_y_vel(0);
				break;
			case 1:
				particles[i].obj_init(graphic, ren, start_x, start_y + 17 - rand() % 34, width, height);
				particles[i].obj_set_x_vel(-5.0 + (rand() % 50) / -10.0);
				particles[i].obj_set_y_vel(0);
				break;
			case 2:
				particles[i].obj_init(graphic, ren, start_x, start_y + 17 - rand() % 34, width, height);
				particles[i].obj_set_x_vel(4.0 + (rand() % 50) / 10.0);
				particles[i].obj_set_y_vel(0);
				break;
			case 3:
				particles[i].obj_init(graphic, ren, start_x, start_y + 17 - rand() % 34, width, height);
				particles[i].obj_set_x_vel(-4.0 + (rand() % 50) / -10.0);
				particles[i].obj_set_y_vel(0);
				break;
			}
		}
	}
	
}

//Emitter updater
void ParticleEmitter::pe_update()
{
	int max_parts = MAX_PARTS;

	if (part_type == 0) {
		max_parts = MAX_PARTS_MISS;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_update_miss();
		}
		
	}

	if (part_type == 1) {
		max_parts = MAX_PARTS_HIT;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_update_hit();
		}
	}
}

//Emitter renderer
void ParticleEmitter::pe_render(SDL_Renderer* ren)
{
	int max_parts = MAX_PARTS;

	if (part_type == 0) {
		max_parts = MAX_PARTS_MISS;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_render_miss(ren);
		}
	}

	if (part_type == 1) {
		max_parts = MAX_PARTS_HIT;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_render_hit(ren);
		}
	}
}

//Particle quit
void ParticleEmitter::pe_quit()
{
	int max_parts = MAX_PARTS;

	if (part_type == 0) {
		max_parts = MAX_PARTS_MISS;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_quit();
		}
	}

	if (part_type == 1) {
		max_parts = MAX_PARTS_HIT;

		for (int i = 0; i < max_parts; i++) {
			particles[i].obj_quit();
		}
	}
}
