/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:28 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/06 17:09:55 by jayzatov         ###   ########.fr       */
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

double	solve_polynom(double a, double b, double c)
{
	double	delta;
	double	t1;
	double	t2;

	delta = b * b - 4 * a * c;
	if (delta == 0.0)
		return (-b / (2.0 * a));
	else if (delta > 0.0)
	{
		t1 = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		t2 = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		if (t1 < 0.0 && t2 < 0.0)
			return (MAXFLOAT);
		if (t1 < 0.0)
			return (t2);
		else if (t2 < 0.0)
			return (t1);
		else
			return (fmin(t1, t2));
	}
	return (MAXFLOAT);
}

// If delta == 0 : intersection in one point

void	solve_poly(double a, double b, double c, t_distances *dst)
{
	double	delta;
	// double	t1;
	// double	t2;
	dst->t1 = MAXFLOAT;
	dst->t2 = MAXFLOAT;
	delta = b * b - 4 * a * c;
	if (delta == 0.0)
	{
		dst->t1 = -b / (2.0 * a);
		// if (!dst->t1)
			// dst->t1 = MAXFLOAT;
		return;
	}
	else if (delta > 0.0)
	{
		dst->t1 = (-b - sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		dst->t2 = (-b + sqrt(b * b - 4.0 * a * c)) / (2.0 * a);
		// if (dst->t1 < 0.0 && dst->t2 < 0.0)
		// {
		// 	dst->t1 = MAXFLOAT;
		// 	dst->t2 = MAXFLOAT;
		// 	return ;
		// 	// return (MAXFLOAT);
		// }
		
		if (dst->t1 < 0.0)
		{
			dst->t1 = MAXFLOAT;
			// return ;
			// return (dst->t2);
		}
		if (dst->t2 < 0.0)
		{
			dst->t2 = MAXFLOAT;
			// return ;
			// return (dst->t1);
		}
		
	}
	
		
	// return (MAXFLOAT);
	
	return;
}

t_vector    find_hit_pt(t_vector origin, t_vector ray, double t_dist)
{
    t_vector ray_norm;
    t_vector pt_on_sphere;

    ray_norm = ray;
    normalize_vector(&ray_norm);
    pt_on_sphere.x = origin.x + (t_dist * ray_norm.x);
    pt_on_sphere.y = origin.y + (t_dist * ray_norm.y);
    pt_on_sphere.z = origin.z + (t_dist * ray_norm.z);

    return (pt_on_sphere);
}


// "distance" : distance between the center of the sphere and the pixel 

void	intersect_sphere(const t_vector eye, const t_vector pixel,
	const t_vector ray, t_object *sphere, t_world world)
{
	t_vector	distance;
	t_vector	pt_on_sphere;
	double		a;
	double		b;
	double		c;

	// le ray va de l'oeil vers le pixel
	// alors que distance va du centre vers le pixel
	distance = create_vector(&sphere->position, &pixel);
	a = dot_product(&ray, &ray);
	b = 2.0 * dot_product(&ray, &distance);
	c = dot_product(&distance, &distance)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	// sphere->t_min = solve_polynom(a, b, c);


	t_distances	dist;
	solve_poly(a, b, c, &dist);
	// dist = two_ts(a, b, c);
	// double min = fmin(dist.t1, dist.t2);
	// double max = fmax(dist.t1, dist.t2);
	// dist.t1 = min;
	// dist.t2 = max;
	

	// t1 et t2, sont respectivement :
	// intersection a la surface, intersection à l'intérieur
	// de la figure
	if (dist.t1 != MAXFLOAT)
	{
		sphere->t_min = dist.t1;
    	pt_on_sphere = find_hit_pt(pixel, ray, sphere->t_min);
		sphere->pt_color = light_on_figure(pt_on_sphere, ray, eye, pixel, ray, sphere->t_min, *sphere, world, 1);
		return;
	}
	else if (dist.t2 != MAXFLOAT)
	{
		sphere->t_min = dist.t2;
    	pt_on_sphere = find_hit_pt(pixel, ray, sphere->t_min);
		sphere->pt_color = light_on_figure(pt_on_sphere, ray, eye, pixel, ray, sphere->t_min, *sphere, world, -1);
		return;
	}
	sphere->t_min = MAXFLOAT;
	sphere->pt_color = sphere->color;
	return;
	(void)world;
	return;
}
