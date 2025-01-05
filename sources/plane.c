/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:29:18 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/05 17:02:35 by jayzatov         ###   ########.fr       */
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


// A plane's fomrula : P is on the plane if : Norm * (P - A_plane_point) = 0.
// It's intersection with a ray fomula : Norm * (Eye + tRay_dir - A_pl_pt)  = 0.
// (Because the ray formula is : Eye + tRay_dir = point).
// So, in "intersect_plane()", we use the formula :
// t = (Norm * (A_pl_pt) - Eye(pixel)) / (Norm * Ray_dir).

void	intersect_plane(const t_vector eye, t_vector pixel, const t_vector ray, t_object *plane, t_world world)
{
	float t = MAXFLOAT;
	int norm_product = 1;
	t_vector on_plane = plane->position;
	t_vector plane_to_pixel =  create_vector(&on_plane, &pixel);
	// normalize_vector(&plane_to_pixel);
	
	// if (dot_product(&plane->direction, &ray) < 0)
		t = -(dot_product(&plane->direction, &plane_to_pixel)
			/ dot_product(&plane->direction, &ray));

	normalize_vector(&plane_to_pixel);
	
	// Utile pour ne pas eclairer la, où les ray de la camera
	// et de la lumiere ne se croisent pas : l'envers du plan

	//norm_product * la norme du plan dans "light_on_figure"
	if (dot_product(&plane->direction, &plane_to_pixel) < 0)
		norm_product *= -1;
		
	if (t >= 0 && t != MAXFLOAT)
	{
		plane->t_min = t;
    	// on_plane = find_hit_pt(pixel, ray, t);
		plane->pt_color = light_on_figure(on_plane, pixel, eye, pixel, ray, t, *plane, world, norm_product);
		return ;
	}
	plane->t_min = MAXFLOAT;
	return ;	
}