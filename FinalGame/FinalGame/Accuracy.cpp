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
	double angle_difference;
	
	if (player->obj_get_x_pos() > object->obj_get_x_pos()) {
		x_overlap = (object->obj_get_x_pos() + object->obj_get_w()) - player->obj_get_x_pos();
	}
	else { x_overlap = (player->obj_get_x_pos() + player->obj_get_w()) - object->obj_get_x_pos(); }
	if (player->obj_get_y_pos() > object->obj_get_y_pos()) {
		y_overlap = (object->obj_get_y_pos() + object->obj_get_h()) - player->obj_get_y_pos();
	}
	else { y_overlap = (player->obj_get_y_pos() + player->obj_get_h()) - object->obj_get_y_pos(); }
	angle_difference = abs(player->obj_get_angle() - object->obj_get_angle());

	std::cout << "x, y overlap: " << x_overlap << ", " << y_overlap << " angle difference: " << angle_difference << std::endl;
	//scaling factor of 40 for angle to make in range of 0-4000 ish
	int difference = (x_overlap * y_overlap) - (angle_difference * 23);
	if ( difference > 0) { 
		return difference; 
	}
	else {
		return 0;
	}
}
