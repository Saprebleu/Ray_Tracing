/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:40:18 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 18:47:38 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

void	color_limit(int *color)
{
	if (*color > 255)
		*color = 255;
	else if (*color < 0)
		*color = 0;
	return ;
}

// The hit point's color would be
// more or less bright.

void	color_is_lit(t_color *color, t_lights lghts, t_object figure)
{
	t_light	amb;
	t_light	spec;
	t_light	diff;

	amb = lghts.ambient;
	spec = lghts.specular;
	diff = lghts.diffuse;
	color->r = figure.color.r * ((amb.r + diff.r + spec.r) / 255.0);
	color_limit(&color->r);
	color->g = figure.color.g * ((amb.g + diff.g + spec.g) / 255.0);
	color_limit(&color->g);
	color->b = figure.color.b * ((amb.b + diff.b + spec.b) / 255.0);
	color_limit(&color->b);
}

// "pixel" in params, stands
// for the eye in the phong
// calculating formula.

t_color	light_n_shade(t_fig_info fig_inf, t_vector pixel,
		t_object figure, t_world world)
{
	t_color		color;
	t_lights	lghts;
	t_lrays		r;
	double		cos_ln;

	r.to_lig = create_vector(&fig_inf.pt_on_figure, &world.light_position);
	lghts.lig_mag = magnitude(r.to_lig);
	r.to_eye = create_vector(&fig_inf.pt_on_figure, &pixel);
	normalize_vector(&r.to_lig);
	normalize_vector(&r.to_eye);
	cos_ln = dot_product(&r.to_lig, &fig_inf.normal);
	light_reflection(&r.l_ref, fig_inf, r.to_lig, cos_ln);
	ambient(fig_inf, &lghts);
	specular(fig_inf, &lghts, r, cos_ln);
	diffuse(fig_inf, &lghts, cos_ln);
	lghts.lig_ray = r.to_lig;
	if (cos_ln >= 0)
		shadows(&lghts, fig_inf, figure);
	color_is_lit(&color, lghts, figure);
	return (color);
}
