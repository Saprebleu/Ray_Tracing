/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:37:17 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/17 18:38:58 by jayzatov         ###   ########.fr       */
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

// The rotation is aplied to vectors that will create a
// rotated ray from a specific point to the figure.

void	translation(t_vector *vec, t_vector new_origin)
{
	vec->x = vec->x - new_origin.x;
	vec->y = vec->y - new_origin.y;
	vec->z = vec->z - new_origin.z;
}

void	detranslation(t_vector *vec, t_vector old_origin)
{
	vec->x += old_origin.x;
	vec->y += old_origin.y;
	vec->z += old_origin.z;
}

void	xyz_rotation_matrix(t_vector original, t_vector *rotated, t_angles angles)
{
	float	alpha;
	float	beta;
	float	gamma;

	alpha = angles.alpha;
	beta = angles.beta;
	gamma = angles.gamma;
	rotated->x = ((cosf(beta) * cosf(gamma)) * original.x)
				+ ((sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma)) * original.y)
				+ ((cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma)) * original.z);
	rotated->y = ((cos(beta) * sin(gamma)) * original.x)
				+ ((sin(alpha) * sin(beta) * sin(gamma) + cos(alpha) * cos(gamma)) * original.y)
				+ ((cos(alpha) * sin(beta) * sin(gamma) - sin(alpha) * cos(gamma)) * original.z);
	rotated->z = ((-sin(beta)) * original.x)
				+ ((sin(alpha) * cos(beta)) * original.y)
				+ ((cos(alpha) * cos(beta)) * original.z);
}

void	rotation_process(t_vector vec, t_vector center, t_vector *rot_vec, t_angles angles)
{
	translation(&vec, center);
	xyz_rotation_matrix(vec, rot_vec, angles);
	detranslation(rot_vec, center);
}