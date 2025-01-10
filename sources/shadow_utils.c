/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:00:27 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/10 14:29:41 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// instead of defining "_GNU_SOURCE",
// to allow portability :

#include <lights.h>

int	t1_limits(double t1, double Ln_mag)
{
	if (t1 != MAXFLOAT && t1 >= 0.01 && t1 <= Ln_mag)
		return (1);
	else
		return (0);
}

int	t2_limits(double t2, double Ln_mag)
{
	if (t2 != MAXFLOAT && t2 >= 0.00001 && t2 <= Ln_mag)
		return (1);
	else
		return (0);
}

int	outside(int in_or_out, t_object *figure, t_object neighbour)
{
	if (in_or_out == 1 && figure->index != neighbour.index)
		return (1);
	else
		return (0);
}

int	inside(int in_or_out)
{
	if (in_or_out == -1)
		return (1);
	else
		return (0);
}

// It may happen that t == t1, with t1 outside the
// cylinder's height, but the t2 is within
// the height and has good length,
// so the shadow is put at the t2 distance;

int	not_cyl_height(double t, t_object neighbour, t_distances dist,
				t_vector L, t_vector pt_on_figure, double Ln_mag)
{
	int	res1;
	int	res2;

	if (neighbour.type == CYLINDER)
	{
		res1 = cylinder_height(&neighbour, dist.t1, L, pt_on_figure);
		res2 = cylinder_height(&neighbour, dist.t2, L, pt_on_figure);
	}
	if (neighbour.type == CYLINDER && t == dist.t1 && res1)
		return (0);
	else if (neighbour.type == CYLINDER && t2_limits(dist.t2, Ln_mag)
		&& res2)
		return (0);
	else if (neighbour.type == CYLINDER && t == dist.t1
		&& (!cylinder_height(&neighbour, dist.t1, L, pt_on_figure)))
		return (1);
	else if (neighbour.type == CYLINDER && t2_limits(dist.t2, Ln_mag)
		&& (!cylinder_height(&neighbour, dist.t2, L, pt_on_figure)))
		return (1);
	return (0);
}
