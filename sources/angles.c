/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:39:43 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/17 18:19:52 by jayzatov         ###   ########.fr       */
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



void	find_angles(t_angles *angles, t_vector rotation, int direction)
{
	angles->alpha = rotation.x * M_PI * direction;
	angles->beta = rotation.y * M_PI * direction;
	angles->gamma = rotation.z * M_PI * direction;
    return ;
}

// void	z_is_one(t_vector *normalized)
// {
// 	normalized->x = 0; 
// 	normalized->y = 0; 
// 	normalized->z = 1;
// }

// void	y_is_one(t_vector *normalized)
// {
// 	normalized->x = 0; 
// 	normalized->y = 1; 
// 	normalized->z = 0;
// }

// void	x_is_one(t_vector *normalized)
// {
// 	normalized->x = 1; 
// 	normalized->y = 0; 
// 	normalized->z = 0;
// }

// float	angle(t_vector direction, char axe)
// {
// 	float		product;
// 	float		d_magn;
// 	float		n_magn;
// 	float 		angle_in_rad;
// 	t_vector	normalized;

// 	if (axe == 'z')
// 		z_is_one(&normalized);
// 	else if (axe == 'y')
// 		y_is_one(&normalized);
// 	else if (axe == 'x')
// 		x_is_one(&normalized);
// 	else
// 		return (361.0f);
// 	product = dot_product(&normalized, &direction);
// 	d_magn  = magnitude(direction);
// 	n_magn  = magnitude(normalized);
// 	angle_in_rad = acosf(product /(d_magn * n_magn));
// 	return (angle_in_rad);
// }

// // Angles vary between -180 and 180 degrees
// // (but are given in radians here).

// void	find_angles(t_angles *angles, t_vector rotation, int direction)
// {
// 	angles->alpha = angle(rotation, 'x') * direction;
// 	angles->beta = angle(rotation, 'y') * direction;
// 	angles->gamma = angle(rotation, 'z') * direction;
//     return ;
// }