/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:00:36 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/06 16:46:19 by jayzatov         ###   ########.fr       */
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
// 	knowing fov degrees (converted to radians for tan()) and screen width.
//  It is the eye-camera distance;

void	initialize_eye(t_vector *eye, t_world world)
{
	t_angles	angles;
	double		camera_distance;

	camera_distance = ((WINDOW_WIDTH / 2.0f)
						/ tan((world.camera_fov / 2.0f) * M_PI / 180.0f));
	eye->x = world.camera_position.x;
	eye->y = world.camera_position.y;
	eye->z = world.camera_position.z - camera_distance;
	find_angles(&angles, world.camera_direction, -1);
	rotation_process(*eye, world.camera_position, eye, angles);
}

void	initialize_pixel(t_vector *pixel, t_world world, int x, int y)
{
	pixel->x = world.camera_position.x - (WINDOW_WIDTH / 2.0f) + x;
	pixel->y = world.camera_position.y + (WINDOW_HEIGHT / 2.0f) - y;
	pixel->z = world.camera_position.z;
}

// static void xyz_rotation_matrix_inverse(t_vector rotated, t_vector *original, t_angles angles)
// {
// 	return;
//     double alpha;
//     double beta;
//     double gamma;

//     alpha = angles.alpha;
//     beta = angles.beta;
//     gamma = angles.gamma;

//     // Matrice transposée (inverse d'une rotation 3D)
//     original->x = ((cos(beta) * cos(gamma)) * rotated.x)
//                 + ((cos(beta) * sin(gamma)) * rotated.y)
//                 + ((-sin(beta)) * rotated.z);

//     original->y = ((sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma)) * rotated.x)
//                 + ((sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma)) * rotated.y)
//                 + ((sin(alpha) * cos(beta)) * rotated.z);

//     original->z = ((cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma)) * rotated.x)
//                 + ((cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma)) * rotated.y)
//                 + ((cos(alpha) * cos(beta)) * rotated.z);
// }

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
