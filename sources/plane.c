/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:29:18 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/15 11:38:41 by jayzatov         ###   ########.fr       */
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
// t = (Norm * (A_pl_pt) - Eye) / (Norm * Ray_dir).

void	intersect_plane(t_vector pixel, const t_vector *ray, t_object *plane)
{
	float t = -1;
	t_vector plane_pt_pixel_prod = create_vector(&pixel, &plane->position);
	
	if (dot_product(&plane->direction, ray) > 0)
		t = dot_product(&plane->direction, &plane_pt_pixel_prod)
			/ dot_product(&plane->direction, ray);
	if (t >= 0)
	{
		plane->t_min = t;
		return ;
	}
	plane->t_min = MAXFLOAT;
	return ;	
}