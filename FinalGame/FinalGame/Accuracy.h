#ifndef CD_H
#define CD_H

#include "GameObject.h"

class Accuracy
{
public:

	static bool check_collision(GameObject* player, GameObject* object);
	static int overlap_area(GameObject* player, GameObject* object);
};
#endif

