/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:24:28 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/13 17:26:12 by jayzatov         ###   ########.fr       */
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

float	solve_polynom(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4 * a * c;
	if (delta == 0.0f)
		return (-b / (2.0f * a));
	else if (delta > 0.0f)
	{
		t1 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		t2 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		if (t1 < 0.0f && t2 < 0.0f)
			return (MAXFLOAT);
		if (t1 < 0.0f)
			return (t2);
		else if (t2 < 0.0f)
			return (t1);
		else
			return (fminf(t1, t2));
	}
	return (MAXFLOAT);
}

// "distance" : distance between the pixel and the center of a sphere

bool	intersect_sphere(const t_vector *pixel,
	const t_vector *ray, t_object *sphere)
{
	t_vector	distance;
	float		a;
	float		b;
	float		c;

	distance = create_vector(&sphere->position, pixel);
	a = dot_product(ray, ray);
	b = 2.0f * dot_product(ray, &distance);
	c = dot_product(&distance, &distance)
		- ((sphere->diameter / 2.0f) * (sphere->diameter / 2.0f));
	sphere->t_min = solve_polynom(a, b, c);
	return (sphere->t_min != MAXFLOAT);
}
