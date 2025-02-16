#include "world.h"

// "Camera distance" is calculated thanks to
// the TOA formula of a right triangle,
// knowing fov degrees (converted to radians for tan()) and screen width.
// It is the eye-camera distance;

void	initialize_eye(t_vector *eye, t_world world)
{
	t_angles	angles;
	double		camera_distance;

	camera_distance = ((WINDOW_WIDTH / 2.0)
			/ tan((world.camera_fov / 2.0) * M_PI / 180.0));
	eye->x = world.camera_position.x;
	eye->y = world.camera_position.y;
	eye->z = world.camera_position.z - camera_distance;
	find_angles(&angles, world.camera_direction, -1);
	rotation_process(*eye, world.camera_position, eye, angles);
}

void	initialize_pixel(t_vector *pixel, t_world world, int x, int y)
{
	pixel->x = world.camera_position.x - (WINDOW_WIDTH / 2.0) + x;
	pixel->y = world.camera_position.y + (WINDOW_HEIGHT / 2.0) - y;
	pixel->z = world.camera_position.z;
}

t_vector	rotated_cam_ray(t_vector *pixel, t_vector *rot_eye, t_world world)
{
	t_angles	angles;
	t_vector	ray;

	find_angles(&angles, world.camera_direction, -1);
	rotation_process(*pixel, world.camera_position, pixel, angles);
	ray = create_vector(rot_eye, pixel);
	normalize_vector(&ray);
	return (ray);
}
