/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:39:43 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 19:01:57 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void	find_angles(t_angles *angles, t_vector rotation, int direction)
{
	angles->alpha = rotation.x * M_PI * direction;
	angles->beta = rotation.y * M_PI * direction;
	angles->gamma = rotation.z * M_PI * direction;
	return ;
}
