/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:29:18 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/16 19:35:40 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700
#include <math.h>
#include <stdio.h>
#include "lights.h"

// A plane's fomrula in 3D: 
// P is on the plane if : Norm * (P - A_plane_point) = 0.
// It's intersection with a ray fomula :
// Norm * (Eye + t * Ray_dir - A_pl_pt) = 0.
// (Because the ray formula is : Eye + t * Ray_dir = point).
// So, to find t :
// t = (Norm * (A_pl_pt) - Eye(pixel)) / (Norm * Ray_dir).
// For readability, in the function, 
// we reverse the A_pl_pt-Eye(pixel) vector.
// (so verifying whether plane_dir and ray
// have the same direction is also reversed :
// "< 0" instead of ">= 0").

void	t_for_plane(t_vector origin, t_vector ray,
			const t_object *plane, t_distances *dist)
{
	t_vector	plane_pt;
	t_vector	pl_to_pxl;

	dist->t1 = MAXFLOAT;
	dist->t2 = MAXFLOAT;
	plane_pt = plane->position;
	pl_to_pxl = create_vector(&plane_pt, &origin);
	if (dot_product(&plane->direction, &ray) != 0)
		dist->t1 = -(dot_product(&plane->direction, &pl_to_pxl)
				/ dot_product(&plane->direction, &ray));
}

// Without this function,
// the plane position must be opposite
// to the plane direction (ex: dir.x = -1
// pos.x = positive number only).
// Otherwise, the light(and shadow)
// would be seen on the wrong side
// of the plane.

void	reversed_plane(int *in_or_out, t_vector pixel, t_object plane)
{
	t_vector	pl_to_pxl;

	pl_to_pxl = create_vector(&plane.position, &pixel);
	normalize_vector(&pl_to_pxl);
	if (dot_product(&plane.direction, &pl_to_pxl) < 0)
		*in_or_out = -1;
}

void	intersect_plane(t_vector pixel, t_vector ray,
		t_object *plane, t_world world)
{
	t_distances	dist;
	t_fig_info	fig_inf;
	t_mirror	a;

	fig_inf.wrld = world;
	fig_inf.in_or_out = 1;
	init_mirror(&a, NULL, pixel, &ray);
	t_for_plane(pixel, ray, plane, &dist);
	reversed_plane(&fig_inf.in_or_out, pixel, *plane);
	if (dist.t1 >= 0 && dist.t1 != MAXFLOAT)
	{
		put_light(plane, dist.t1, fig_inf, a);
		return ;
	}
	plane->t_min = MAXFLOAT;
}
