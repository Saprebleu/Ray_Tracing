/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:39:43 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/13 16:08:30 by jayzatov         ###   ########.fr       */
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

void	z_is_one(t_vector *normalized)
{
	normalized->x = 0; 
	normalized->y = 0; 
	normalized->z = 1;
}

void	y_is_one(t_vector *normalized)
{
	normalized->x = 0; 
	normalized->y = 1; 
	normalized->z = 0;
}

void	x_is_one(t_vector *normalized)
{
	normalized->x = 1; 
	normalized->y = 0; 
	normalized->z = 0;
}

float	angle(t_vector direction, char axe)
{
	float		product;
	float		d_magn;
	float		n_magn;
	float 		angle_in_rad;
	t_vector	normalized;

	if (axe == 'z')
		z_is_one(&normalized);
	else if (axe == 'y')
		y_is_one(&normalized);
	else if (axe == 'x')
		x_is_one(&normalized);
	else
		return (361.0f);
	product = dot_product(&normalized, &direction);
	d_magn  = magnitude(direction);
	n_magn  = magnitude(normalized);
	angle_in_rad = acosf(product /(d_magn * n_magn));
	return (angle_in_rad);
}

// Angles vary between 0 and 180 degrees
// (but are given in radians here).

void	find_angles(t_angles *angles, t_vector cylinder_direction)
{
	angles->alpha = angle(cylinder_direction, 'x') * (-1);
	angles->beta = angle(cylinder_direction, 'y') * (-1);
	angles->gamma = angle(cylinder_direction, 'z') * (-1);
    return ;
}