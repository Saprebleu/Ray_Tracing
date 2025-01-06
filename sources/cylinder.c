/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:41 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/06 16:48:20 by jayzatov         ###   ########.fr       */
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

t_distances	two_ts(double a, double b, double c)
{
	double	delta;
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
		dist.t1 = (-b - sqrt(b * b - 4.0f * a * c)) / (2.0f * a);
		dist.t2 = (-b + sqrt(b * b - 4.0f * a * c)) / (2.0f * a);
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
	double		a;
	double		b;
	double		c;
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
 
bool	cylinder_height(t_object *cylinder, double t,
		t_vector ray, t_vector rot_pixel)
{
	t_vector	figure_point;
	double		point_center_length;
	double		pythagore_solution;
	
	cylinder->t_min = t;
	// printf("      cylinder->t_min %f\n", cylinder->t_min);
	figure_point.x = rot_pixel.x + (cylinder->t_min * ray.x);
	figure_point.y = rot_pixel.y + (cylinder->t_min * ray.y);
	figure_point.z = rot_pixel.z + (cylinder->t_min * ray.z);
	// a^2 + b^2 = c^2
 	point_center_length = sqrt(square((figure_point.x - cylinder->position.x)) +
						  square((figure_point.y - cylinder->position.y)) +
						  square((figure_point.z - cylinder->position.z)));
	
	// b^2 = c^2 - a^2
	pythagore_solution = square(point_center_length) - square((cylinder->diameter / 2.0f));
	pythagore_solution = sqrt(pythagore_solution);
	
	
	// printf("pythagore_solution %f\n", pythagore_solution);
	// printf("(cylinder->height / 2.0f) %f\n", (cylinder->height / 2.0f));
	if (point_center_length <= cylinder->diameter / 2.0f)
		return (true);

	double mid_height = cylinder->height / 2.0f;

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

// static t_vector    find_hit_pt(t_vector origin, t_vector ray, double t_dist)
// {
//     t_vector ray_norm;
//     t_vector pt_on_sphere;

//     ray_norm = ray;
//     normalize_vector(&ray_norm);
//     pt_on_sphere.x = origin.x + (t_dist * ray_norm.x);
//     pt_on_sphere.y = origin.y + (t_dist * ray_norm.y);
//     pt_on_sphere.z = origin.z + (t_dist * ray_norm.z);

//     return (pt_on_sphere);
// }

extern int x;
extern int y;
void	intesect_cylinder(t_vector	eye, t_vector pixel, t_object *cylinder, t_world world)
{
	t_angles	angles;
	t_vector	rot_eye;
	t_vector	rot_pixel;
	t_vector	ray;
	t_distances	dist;


	t_vector origin_pt;
	origin_pt.x = MAXFLOAT;
	origin_pt.y = MAXFLOAT;
	origin_pt.z = MAXFLOAT;
	
	find_angles(&angles, cylinder->direction, -1);
	
	rotation_process(eye, cylinder->position, &rot_eye, angles);
	rotation_process(pixel, cylinder->position, &rot_pixel, angles);

	t_vector rot_ray = create_vector(&rot_eye, &rot_pixel);
	ray = create_vector(&eye, &pixel);
	normalize_vector(&rot_ray);
	dist = find_distances(rot_ray, rot_pixel, *cylinder);

	if (dist.t1 != MAXFLOAT && cylinder_height(cylinder, dist.t1, rot_ray, rot_pixel))
	{
		origin_pt = find_hit_pt(pixel, ray, dist.t1);
		cylinder->pt_color = light_on_figure(origin_pt, pixel, rot_eye, rot_pixel, rot_ray, dist.t1, *cylinder, world, 1);
		cylinder->t_min = dist.t1;
		return;
	}
	if (dist.t2 != MAXFLOAT && cylinder_height(cylinder, dist.t2, rot_ray, rot_pixel))
	{
		origin_pt = find_hit_pt(pixel, ray, dist.t2);
		cylinder->pt_color = light_on_figure(origin_pt, pixel, rot_eye, rot_pixel, rot_ray, dist.t2, *cylinder, world, -1);
		cylinder->t_min = dist.t2;
		return;
	}
	cylinder->pt_color = cylinder->color;
	cylinder->t_min = MAXFLOAT;
	
	
	return;
}