#ifndef PE_H
#define PE_H

#include "Particle.h"
#include "screenInfo.h"

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	void pe_init(const char* graphic, SDL_Renderer* ren, int start_x, int start_y, int width, int height, int type);

	void pe_update();
	void pe_render(SDL_Renderer* ren);

	void pe_quit();
	bool pe_started;

private:
	Particle particles[MAX_PARTS];
	int pos_x, pos_y;
	int part_type;
};
#endif
