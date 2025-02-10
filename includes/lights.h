/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:26:39 by jayzatov          #+#    #+#             */
/*   Updated: 2025/02/10 15:25:21 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H
# define _XOPEN_SOURCE 700
# include <math.h>
# include "world.h"

typedef struct s_lrays
{
	t_vector	to_lig;
	t_vector	to_eye;
	t_vector	l_ref;
}	t_lrays;

typedef struct s_sha_data
{
	t_distances	dist;
	t_object	neighbour;
	t_vector	pt_origin;
	t_vector	rot_light;
	t_vector	l_ray;
	double		l_mag;
	double		t;
}	t_sha_data;

void		put_light(t_object *figure, float t,
				t_fig_info fig_inf, t_mirror a);
t_color		light_n_shade(t_fig_info fig_inf, t_vector pixel,
				t_object figure, t_world world);
void		light_reflection(t_vector *ref_lght, t_fig_info fig_inf,
				t_vector to_light, double cos_l_norm);
void		plane_norm(t_fig_info *fig_inf, t_object plane);
void		sphere_norm(t_fig_info *fig_inf, t_object sphere);
void		cylinder_norm(t_fig_info *fig_inf, t_vector pt_on_cyl,
				t_object cylinder);
void		ambient(t_fig_info f_i, t_lights *lights);
void		specular(t_fig_info f_i, t_lights *lights,
				t_lrays r, double cos_l_norm);
void		diffuse(t_fig_info f_i, t_lights *lights, double cos_l_norm);
void		shadows(t_lights *lights, t_fig_info finfo, t_object figure);
int			t1_limits(double t1, double Ln_mag);
int			t2_limits(double t2, double Ln_mag);
int			outside(int in_or_out, t_object figure, t_object neighbour);
int			inside(int in_or_out);
void		t_n_lmag(t_sha_data *shdw, t_object neighbour);
int			not_cyl_height(t_sha_data shdw, t_object neighbour);

#endif