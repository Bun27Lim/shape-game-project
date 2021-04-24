#ifndef CD_H
#define CD_H

#include "PlayerShape.h"
#include "GameObject.h"

class Accuracy
{
public:
	Accuracy();
	~Accuracy();

	bool check_collision(PlayerShape*, GameObject*);
};
#endif

