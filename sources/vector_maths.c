/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:53:00 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/14 16:48:09 by jayzatov         ###   ########.fr       */
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

t_vector	create_vector(const t_vector *start, const t_vector *end)
{
	t_vector	v;

	v.x = end->x - start->x;
	v.y = end->y - start->y;
	v.z = end->z - start->z;
	return (v);
}

// Gives a number resulting of the multiplication of 2 vectors.
// The dot product can be useful to :
// 		- calcualte the distance.
//		- determine angles.
//		- determine whether an object is aiming towards another
//		  or the contrary...

float	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

// Written |V|

float	magnitude(t_vector vec)
{
	float	magnitude;

	magnitude = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
	return (magnitude);
}

void	normalize_vector(t_vector *v)
{
	float	length;

	length = sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

float	square(float nbr)
{
	return (nbr * nbr);
}
