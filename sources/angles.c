#include "world.h"

void	find_angles(t_angles *angles, t_vector rotation, int direction)
{
	angles->alpha = rotation.x * M_PI * direction;
	angles->beta = rotation.y * M_PI * direction;
	angles->gamma = rotation.z * M_PI * direction;
	return ;
}
