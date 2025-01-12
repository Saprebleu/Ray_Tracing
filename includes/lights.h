/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:26:39 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 18:14:42 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H


# define _XOPEN_SOURCE 700
# include <math.h>
# include "world.h"
// #include <stdlib.h>
// #include <stdio.h>

typedef struct s_lrays
{
	t_vector to_lig;
    t_vector to_eye;
    t_vector l_ref;
}	t_lrays;

typedef struct s_sha_data
{
	t_distances	dist;
    t_object	neighbour;
    t_vector	pt_origin;
	t_vector	rot_light;
	t_vector		l_ray;
	double		l_mag;
    double      t;
}	t_sha_data;

void	light_reflection(t_vector *ref_lght, t_fig_info fig_inf, t_vector to_light,
	    double	cos_l_norm);
void		shadows(t_lights *lghts, t_fig_info finfo, t_object figure);
int			t1_limits(double t1, double Ln_mag);
int			t2_limits(double t2, double Ln_mag);
int			outside(int in_or_out, t_object figure, t_object neighbour);
int			inside(int in_or_out);
void	ambient(t_fig_info f_i, t_lights *lghts);
void	specular(t_fig_info f_i, t_lights *lghts, t_lrays r,
        double	cos_l_norm);
void	diffuse(t_fig_info f_i, t_lights *lghts, double cos_l_norm);
void		t_n_lmag(t_sha_data *shdw, t_object neighbour);
int     not_cyl_height(t_sha_data shdw, t_object neighbour);

#endif