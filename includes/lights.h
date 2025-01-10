/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:26:39 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/10 14:43:59 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# define _XOPEN_SOURCE 700
# include <math.h>
# include "world.h"

typedef struct s_light
{
    int r;
    int g;
    int b;
} t_light;

typedef struct s_lights
{
    t_light specular;
    t_light diffuse;
    t_light ambient;
}   t_lights;

typedef struct s_lrays
{
	t_vector to_lig;
    t_vector to_eye;
    t_vector l_ref;
}	t_lrays;

void	light_reflection(t_vector *ref_lght, t_fig_info fig_inf, t_vector to_light,
	    double	cos_l_norm);
void	ambient(t_fig_info f_i, t_lights *lghts);
void	specular(t_fig_info f_i, t_lights *lghts, t_lrays r,
        double	cos_l_norm);
void	diffuse(t_fig_info f_i, t_lights *lghts, double cos_l_norm);

#endif