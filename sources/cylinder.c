/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:41 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/14 19:54:38 by jayzatov         ###   ########.fr       */
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

t_distances	two_ts(float a, float b, float c)
{
	float	delta;
	t_distances dist;

	dist.t1 = MAXFLOAT;
	dist.t2 = MAXFLOAT;
	delta = b * b - 4 * a * c;
	if (delta == 0.0f)
	{
		dist.t1 = -b / (2.0f * a);
		return (dist);
	}
	else if (delta > 0.0f)
	{
		dist.t1 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		dist.t2 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
	}
	return (dist);	
}

// Those are two (or only one) distances(t) between
// the pixel and the figure points intersected
// by the ray from that pixel.

t_distances	find_distances(t_vector ray, t_vector rot_pixel, t_object figure)
{
	float		a;
	float		b;
	float		c;
	t_vector	fig_pixel_dist;

	fig_pixel_dist = create_vector(&figure.position, &rot_pixel);
	a = (ray.x * ray.x + ray.z * ray.z);
	b = 2.0f * (ray.x * fig_pixel_dist.x) + 2.0f * (ray.z * fig_pixel_dist.z);
	c = (fig_pixel_dist.x * fig_pixel_dist.x + fig_pixel_dist.z * fig_pixel_dist.z)
		- ((figure.diameter / 2.0f) * (figure.diameter / 2.0f));
	return (two_ts(a, b, c));
}

// "figure_point" is the point on the finite cylinder
// that might be touched by the ray.
 
bool	cylinder_height(t_object *cylinder, float t,
		t_vector ray, t_vector rot_pixel)
{
	t_vector	figure_point;
	float		point_center_length;
	float		pythagore_solution;
	
	cylinder->t_min = t;
	// printf("      cylinder->t_min %f\n", cylinder->t_min);
	figure_point.x = rot_pixel.x + (cylinder->t_min * ray.x);
	figure_point.y = rot_pixel.y + (cylinder->t_min * ray.y);
	figure_point.z = rot_pixel.z + (cylinder->t_min * ray.z);
	point_center_length = (square((figure_point.x - cylinder->position.x)) +
								square((figure_point.y - cylinder->position.y))+
								square((figure_point.z - cylinder->position.z)));
	pythagore_solution = point_center_length - square((cylinder->diameter / 2.0f));
	pythagore_solution = sqrtf(pythagore_solution);
	if (fabsf(pythagore_solution) <= (cylinder->height / 2.0f))
		return (cylinder->t_min != MAXFLOAT);
	return (false);
}

// In the "find_distances" function,"cylinder->direction" isn't used.
// In the "find_angles" funciton, we create a normalized vector for
// each axe (x, y, z).
// So we don't need to normalize "cylinder->direction" here.

void	intesect_cylinder(t_vector	eye, t_vector pixel, t_object *cylinder)
{
	t_angles	angles;
	t_vector	rot_eye;
	t_vector	rot_pixel;
	t_vector	ray;
	t_distances	dist;

	find_angles(&angles, cylinder->direction);
	rotation_process(eye, cylinder->position, &rot_eye, angles);
	rotation_process(pixel, cylinder->position, &rot_pixel, angles);
	ray = create_vector(&rot_eye, &rot_pixel);
	normalize_vector(&ray);
	dist = find_distances(ray, rot_pixel, *cylinder);
	if (dist.t1 != MAXFLOAT && cylinder_height(cylinder, dist.t1, ray, rot_pixel))
		return;
	if (dist.t2 != MAXFLOAT && cylinder_height(cylinder, dist.t2, ray, rot_pixel))
		return;
	cylinder->t_min = MAXFLOAT;
	return;
}