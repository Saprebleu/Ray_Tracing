/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:37:17 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 19:03:53 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

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

void	xyz_rotation_matrix(t_vector original,
		t_vector *rotated, t_angles angles)
{
	double	alp;
	double	bet;
	double	gam;

	alp = angles.alpha;
	bet = angles.beta;
	gam = angles.gamma;
	rotated->x = ((cos(bet) * cos(gam)) * original.x)
		+ ((sin(alp) * sin(bet) * cos(gam) - cos(alp) * sin(gam)) * original.y)
		+ ((cos(alp) * sin(bet) * cos(gam) + sin(alp) * sin(gam)) * original.z);
	rotated->y = ((cos(bet) * sin(gam)) * original.x)
		+ ((sin(alp) * sin(bet) * sin(gam) + cos(alp) * cos(gam)) * original.y)
		+ ((cos(alp) * sin(bet) * sin(gam) - sin(alp) * cos(gam)) * original.z);
	rotated->z = ((-sin(bet)) * original.x)
		+ ((sin(alp) * cos(bet)) * original.y)
		+ ((cos(alp) * cos(bet)) * original.z);
}

t_vector	rotation_process(t_vector vec, t_vector center,
			t_vector *rot_vec, t_angles angles)
{
	translation(&vec, center);
	xyz_rotation_matrix(vec, rot_vec, angles);
	detranslation(rot_vec, center);
	return (*rot_vec);
}
