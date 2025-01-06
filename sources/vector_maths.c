/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:53:00 by jayzatov          #+#    #+#             */
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
// - calcualte the distance.
// - determine whether an object is aiming towards another
//  or the contrary by determining angles :
//  by calculating the cosinus (dot product) between
//  two normalized vectors : which gives smth in the
//  range [-1 ; 1] in radians.
//  If the cos < 0, the vectors don't have the same
//  direction. At cos == 1 they're orthogonal...

double	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

// Written |V|, used on not normalized vectors
// because it measures the vector's length.

double	magnitude(t_vector vec)
{
	double	magnitude;

	magnitude = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (magnitude);
}

// Particularly useful to extract the
// vector's direction, without its length.

void	normalize_vector(t_vector *v)
{
	double	length;

	length = sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

double	square(double nbr)
{
	return (nbr * nbr);
}
