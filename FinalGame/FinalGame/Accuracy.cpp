#include "Accuracy.h"


/// **************************************************************** ///
/// Check whether or not the playershape and an object are touching
/// **************************************************************** ///
bool Accuracy::check_collision(GameObject* player, GameObject* object)
{
	if (player->obj_get_x_pos() > (object->obj_get_x_pos() + object->obj_get_w())) return false;
	if ((player->obj_get_x_pos() + player->obj_get_w()) < object->obj_get_x_pos()) return false;
	if (player->obj_get_y_pos() > (object->obj_get_y_pos() + object->obj_get_h())) return false;
	if ((player->obj_get_y_pos() + player->obj_get_h()) < object->obj_get_y_pos()) return false;
	return true;
}

int Accuracy::overlap_area(GameObject* player, GameObject* object)
{
	int x_overlap, y_overlap;
	
	x_overlap = (player->obj_get_x_pos() + player->obj_get_w()) - object->obj_get_x_pos();
	y_overlap = (player->obj_get_y_pos() + player->obj_get_h()) - object->obj_get_y_pos();

	return x_overlap*y_overlap;
}
