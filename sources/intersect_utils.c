/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:26:06 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/13 10:34:05 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lights.h"

// For cylinder : eye and pixel.
// For plane and sphere : pixel and ray.

void	init_mirror(t_mirror *a, t_vector *eye, t_vector pixel, t_vector *ray)
{
	if (eye != NULL)
	{
		a->strt = *eye;
		a->rot_strt = *eye;
	}
	a->dir = pixel;
	a->rot_dir = pixel;
	if (ray != NULL)
		a->ray = *ray;
}

t_vector	find_hit_pt(t_vector origin, t_vector ray, double t_dist)
{
	t_vector	ray_norm;
	t_vector	pt_on_sphere;

	ray_norm = ray;
	normalize_vector(&ray_norm);
	pt_on_sphere.x = origin.x + (t_dist * ray_norm.x);
	pt_on_sphere.y = origin.y + (t_dist * ray_norm.y);
	pt_on_sphere.z = origin.z + (t_dist * ray_norm.z);
	return (pt_on_sphere);
}

void	put_light(t_object *figure, float t, t_fig_info fig_inf, t_mirror a)
{
	t_vector	pixel;

	pixel = a.dir;
	fig_inf.pt_on_figure = find_hit_pt(pixel, a.ray, t);
	if (figure->type == SPHERE)
		sphere_norm(&fig_inf, *figure);
	else if (figure->type == CYLINDER)
		cylinder_norm(&fig_inf, fig_inf.pt_on_figure, *figure);
	else if (figure->type == PLANE)
		plane_norm(&fig_inf, *figure);
	figure->pt_color = light_n_shade(fig_inf, a.dir, *figure,
			fig_inf.wrld);
	figure->t_min = t;
}
