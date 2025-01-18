/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:28 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/13 18:28:35 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"
#include <math.h>
#include <stdio.h>

// If delta == 0 : intersection in one point

void	solve_polynom(double a, double b, double c, t_distances *dst)
{
	double	delta;

	dst->t1 = MAXFLOAT;
	dst->t2 = MAXFLOAT;
	delta = b * b - 4 * a * c;
	if (delta == 0.0)
	{
		dst->t1 = -b / (2.0 * a);
		return ;
	}
	else if (delta > 0.0)
	{
		dst->t1 = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		dst->t2 = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		if (dst->t1 < 0.0)
			dst->t1 = MAXFLOAT;
		if (dst->t2 < 0.0)
			dst->t2 = MAXFLOAT;
	}
	return ;
}

void	t_for_sphere(t_vector origin, t_vector ray, const t_object *sphere,
		t_distances *dist)
{
	t_vector	distance;
	double		a;
	double		b;
	double		c;

	distance = create_vector(&sphere->position, &origin);
	a = dot_product(&ray, &ray);
	b = 2.0 * dot_product(&ray, &distance);
	c = dot_product(&distance, &distance)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	solve_polynom(a, b, c, dist);
}

// t1 is on the outside, while
// t2 is on the inside of the figure.

void	intersect_sphere(t_vector pixel, t_vector ray,
		t_object *sphere, t_world world)
{
	t_distances	dist;
	t_fig_info	fig_inf;
	t_mirror	a;

	fig_inf.wrld = world;
	init_mirror(&a, NULL, pixel, &ray);
	t_for_sphere(pixel, ray, sphere, &dist);
	if (dist.t1 >= 0 && dist.t1 != MAXFLOAT)
	{
		fig_inf.in_or_out = 1;
		put_light(sphere, dist.t1, fig_inf, a);
		return ;
	}
	else if (dist.t2 >= 0 && dist.t2 != MAXFLOAT)
	{
		fig_inf.in_or_out = -1;
		put_light(sphere, dist.t2, fig_inf, a);
		return ;
	}
	sphere->t_min = MAXFLOAT;
	sphere->pt_color = sphere->color;
}
