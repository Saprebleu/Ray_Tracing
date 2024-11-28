/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:41 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/28 13:56:04 by jayzatov         ###   ########.fr       */
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
		if (dist.t1 < 0)
			dist.t1 = MAXFLOAT;
		if (dist.t2 < 0)
			dist.t2 = MAXFLOAT;
		
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
	// a^2 + b^2 = c^2
 	point_center_length = sqrtf(square((figure_point.x - cylinder->position.x)) +
						  square((figure_point.y - cylinder->position.y)) +
						  square((figure_point.z - cylinder->position.z)));
	
	// b^2 = c^2 - a^2
	pythagore_solution = square(point_center_length) - square((cylinder->diameter / 2.0f));
	pythagore_solution = sqrtf(pythagore_solution);
	
	
	// printf("pythagore_solution %f\n", pythagore_solution);
	// printf("(cylinder->height / 2.0f) %f\n", (cylinder->height / 2.0f));
	if (point_center_length <= cylinder->diameter / 2.0f)
		return (true);

	float mid_height = cylinder->height / 2.0f;

	// printf("mid_height %f\n", mid_height);

	// if (pythagore_solution < mid_height/2 && point_center_length > 0)
	// 	return (true);
	if (pythagore_solution <= mid_height)
		return (true);
	return (false);
}

// In the "find_distances" function,"cylinder->direction" isn't used.
// In the "find_angles" funciton, we create a normalized vector for
// each axe (x, y, z).
// So we don't need to normalize "cylinder->direction" here.

void	intesect_cylinder(t_vector	eye, t_vector pixel, t_object *cylinder, t_world world)
{
	t_angles	angles;
	t_vector	rot_eye;
	t_vector	rot_pixel;
	t_vector	ray;
	t_distances	dist;

	find_angles(&angles, cylinder->direction, -1);
	// printf("alpha %f\n", angles.alpha/M_PI * 180);
	// printf("beta %f\n", angles.beta/M_PI * 180);
	// printf("gamma %f\n", angles.gamma/M_PI * 180); 
	
	rotation_process(eye, cylinder->position, &rot_eye, angles);
	rotation_process(pixel, cylinder->position, &rot_pixel, angles);
	ray = create_vector(&rot_eye, &rot_pixel);
	normalize_vector(&ray);
	dist = find_distances(ray, rot_pixel, *cylinder);
	
	if (dist.t1 != MAXFLOAT && cylinder_height(cylinder, dist.t1, ray, rot_pixel))
	{
		cylinder->pt_color = light_on_figure(rot_pixel, ray, dist.t1, *cylinder, world, 1);
		cylinder->t_min = dist.t1;
		return;
	}
	if (dist.t2 != MAXFLOAT && cylinder_height(cylinder, dist.t2, ray, rot_pixel))
	{
		cylinder->pt_color = light_on_figure(rot_pixel, ray, dist.t2, *cylinder, world, -1);
		cylinder->t_min = dist.t2;
		// cylinder->t_min = MAXFLOAT;

		return;
	}
	cylinder->pt_color = cylinder->color;
	cylinder->t_min = MAXFLOAT;
	
	
	return;
}