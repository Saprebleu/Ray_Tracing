/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:00:36 by jayzatov          #+#    #+#             */
/*   Updated: 2024/12/02 16:16:21 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "mlx.h"

#include "world.h"
#include "parsing.h"


// "Camera distance" is calculated thanks to the TOA formula of a right triangle,
// 	knowing fov degrees (converted to radians for tanf()) and screen width.
//  It is the eye-camera distance;

void	initialize_eye(t_vector *eye, t_world world)
{
	float		camera_distance;

	camera_distance = ((WINDOW_WIDTH / 2.0f)
						/ tanf((world.camera_fov / 2.0f) * M_PI / 180.0f));
	eye->x = world.camera_position.x;
	eye->y = world.camera_position.y;
	eye->z = world.camera_position.z - camera_distance;
}

void	initialize_pixel(t_vector *pixel, t_world world, int x, int y)
{
	pixel->x = world.camera_position.x - (WINDOW_WIDTH / 2.0f) + x;
	pixel->y = world.camera_position.y + (WINDOW_HEIGHT / 2.0f) - y;
	pixel->z = world.camera_position.z;
}

t_vector	rotated_cam_ray(t_vector *pixel, t_vector *eye, t_world world)
{
	t_angles	angles;
	t_vector	ray;

	find_angles(&angles, world.camera_direction, -1);
	rotation_process(*pixel, world.camera_position, pixel, angles);
	rotation_process(*eye, world.camera_position, eye, angles);
	ray = create_vector(eye, pixel);
	normalize_vector(&ray);
	return (ray);
}
