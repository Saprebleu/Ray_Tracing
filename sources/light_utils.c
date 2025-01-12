/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:25:11 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 18:49:30 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

void	light_reflection(t_vector *ref_lght, t_fig_info fig_inf,
		t_vector to_light, double cos_l_norm)
{
	cos_l_norm = dot_product(&to_light, &fig_inf.normal);
	ref_lght->x = 2 * cos_l_norm * fig_inf.normal.x - to_light.x;
	ref_lght->y = 2 * cos_l_norm * fig_inf.normal.y - to_light.y;
	ref_lght->z = 2 * cos_l_norm * fig_inf.normal.z - to_light.z;
	normalize_vector(ref_lght);
}

void	ambient(t_fig_info f_i, t_lights *lghts)
{
	t_world	world;

	world = f_i.wrld;
	lghts->ambient.r = world.ambient_power * world.ambient_color.r;
	lghts->ambient.g = world.ambient_power * world.ambient_color.g;
	lghts->ambient.b = world.ambient_power * world.ambient_color.b;
}

void	specular(t_fig_info f_i, t_lights *lghts,
		t_lrays r, double cos_l_norm)
{
	t_world	world;
	double	cos_ref_cam;

	world = f_i.wrld;
	cos_ref_cam = dot_product(&r.l_ref, &r.to_eye);
	if (cos_ref_cam > 0.0 && cos_l_norm > 0.0)
	{
		lghts->specular.r = pow(dot_product(&r.l_ref, &r.to_eye), SHINE)
			* world.light_power * world.light_color.r;
		lghts->specular.g = pow(dot_product(&r.l_ref, &r.to_eye), SHINE)
			* world.light_power * world.light_color.g;
		lghts->specular.b = pow(dot_product(&r.l_ref, &r.to_eye), SHINE)
			* world.light_power * world.light_color.b;
	}
	else
	{
		lghts->specular.r = 0;
		lghts->specular.g = 0;
		lghts->specular.b = 0;
	}
}

void	diffuse(t_fig_info f_i, t_lights *lghts, double cos_l_norm)
{
	t_world	world;

	world = f_i.wrld;
	if (cos_l_norm < 0.0)
		cos_l_norm = 0.0;
	lghts->diffuse.r = cos_l_norm * (world.light_power * world.light_color.r);
	lghts->diffuse.g = cos_l_norm * (world.light_power * world.light_color.g);
	lghts->diffuse.b = cos_l_norm * (world.light_power * world.light_color.b);
}
