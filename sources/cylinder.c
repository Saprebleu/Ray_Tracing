/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:41 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/13 10:34:27 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "lights.h"

t_vector	rotated(t_vector *eye, t_vector *pixel, t_object cylinder)
{
	t_angles	angles;
	t_vector	rot_eye;
	t_vector	rot_pixel;
	t_vector	rot_ray;

	find_angles(&angles, cylinder.direction, -1);
	rotation_process(*eye, cylinder.position, &rot_eye, angles);
	rotation_process(*pixel, cylinder.position, &rot_pixel, angles);
	rot_ray = create_vector(&rot_eye, &rot_pixel);
	normalize_vector(&rot_ray);
	*pixel = rot_pixel;
	*eye = rot_eye;
	return (rot_ray);
}

// Those are two (or only one) distances(t) between
// the pixel and the figure points intersected
// by the ray from the pixel.
// But since cylinders can be rotated,
// we need to reverse-rotate the ray
// before looking for t1 and t2.

void	t_for_cylinder(t_vector rot_pixel, t_vector rot_ray, t_object cylinder,
	t_distances *dist)
{
	double		a;
	double		b;
	double		c;
	t_vector	fig_to_pxl;

	fig_to_pxl = create_vector(&cylinder.position, &rot_pixel);
	a = (rot_ray.x * rot_ray.x + rot_ray.z * rot_ray.z);
	b = 2.0 * (rot_ray.x * fig_to_pxl.x) + 2.0 * (rot_ray.z * fig_to_pxl.z);
	c = (fig_to_pxl.x * fig_to_pxl.x + fig_to_pxl.z * fig_to_pxl.z)
		- ((cylinder.diameter / 2.0) * (cylinder.diameter / 2.0));
	solve_polynom(a, b, c, dist);
}

t_vector	cyl_distances(t_vector *start, t_vector *dir,
		const t_object *cylinder, t_distances *dist)
{
	t_vector	rot_ray;

	rot_ray = rotated(start, dir, *cylinder);
	normalize_vector(&rot_ray);
	t_for_cylinder(*dir, rot_ray, *cylinder, dist);
	return (rot_ray);
}

// "figure_point" is the point on the finite cylinder
// that might be touched by the ray :
// Fig_p = origin + t * Dir.
// For the "point_center_length", the
// formula "a^2 + b^2 = c^2" is used.
// For the "pythagore_solution", the
// formula "b^2 = c^2 - a^2" is used.

bool	cylinder_height(t_object *cylinder, double t,
		t_vector ray, t_vector rot_pixel)
{
	t_vector	figure_point;
	double		point_center_length;
	double		pythagore_solution;
	double		mid_height;

	cylinder->t_min = t;
	figure_point.x = rot_pixel.x + (cylinder->t_min * ray.x);
	figure_point.y = rot_pixel.y + (cylinder->t_min * ray.y);
	figure_point.z = rot_pixel.z + (cylinder->t_min * ray.z);
	point_center_length = sqrt(square((figure_point.x
					- cylinder->position.x))
			+ square((figure_point.y - cylinder->position.y))
			+ square((figure_point.z - cylinder->position.z)));
	if (point_center_length <= cylinder->diameter / 2.0)
		return (true);
	pythagore_solution = square(point_center_length)
		- square((cylinder->diameter / 2.0));
	pythagore_solution = sqrt(pythagore_solution);
	mid_height = cylinder->height / 2.0;
	if (pythagore_solution <= mid_height)
		return (true);
	return (false);
}

void	intesect_cylinder(t_vector pixel, t_vector eye, t_object *cylinder,
		t_world world)
{
	t_distances	dist;
	t_fig_info	fig_inf;
	t_mirror	a;

	fig_inf.wrld = world;
	init_mirror(&a, &eye, pixel, NULL);
	a.ray = create_vector(&eye, &pixel);
	normalize_vector(&a.ray);
	a.rot_ray = cyl_distances(&a.rot_strt, &a.rot_dir, cylinder, &dist);
	if (dist.t1 >= 0 && dist.t1 != MAXFLOAT
		&& cylinder_height(cylinder, dist.t1, a.rot_ray, a.rot_dir))
	{
		fig_inf.in_or_out = 1;
		put_light(cylinder, dist.t1, fig_inf, a);
		return ;
	}
	else if (dist.t2 >= 0 && dist.t2 != MAXFLOAT
		&& cylinder_height(cylinder, dist.t2, a.rot_ray, a.rot_dir))
	{
		fig_inf.in_or_out = -1;
		put_light(cylinder, dist.t2, fig_inf, a);
		return ;
	}
	cylinder->pt_color = cylinder->color;
	cylinder->t_min = MAXFLOAT;
}
