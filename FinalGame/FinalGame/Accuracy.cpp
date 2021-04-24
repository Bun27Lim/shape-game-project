#include "Accuracy.h"

Accuracy::Accuracy()
{
}

Accuracy::~Accuracy()
{
}

/// **************************************************************** ///
/// Check whether or not the playershape and an object are touching
/// **************************************************************** ///
bool Accuracy::check_collision(PlayerShape* player, GameObject* object)
{
	//if (player->obj_get_x_pos() > (object->obj_get_x_pos() + object->obj_get_w())) return false;
	//if ((player->obj_get_x_pos() + player->obj_get_w()) < object->obj_get_x_pos()) return false;
	//if (player->obj_get_y_pos() > (object->obj_get_y_pos() + object->obj_get_h())) return false;
	//if ((player->obj_get_y_pos() + player->obj_get_h()) < object->obj_get_y_pos()) return false;
	return false;
}
