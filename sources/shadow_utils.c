#include "lights.h"

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

int	outside(int in_or_out, t_object figure, t_object neighbour)
{
	if (in_or_out == 1 && figure.index != neighbour.index)
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
// this height and has good length,
// so the shadow is put at the t2 distance;

int	not_cyl_height(t_sha_data shdw, t_object neighbour)
{
	int	res1;
	int	res2;

	if (neighbour.type == CYLINDER)
	{
		res1 = cylinder_height(&neighbour, shdw.dist.t1,
				shdw.l_ray, shdw.pt_origin);
		res2 = cylinder_height(&neighbour, shdw.dist.t2,
				shdw.l_ray, shdw.pt_origin);
	}
	if (neighbour.type == CYLINDER && shdw.t == shdw.dist.t1 && res1)
		return (0);
	else if (neighbour.type == CYLINDER && t2_limits(shdw.dist.t2, shdw.l_mag)
		&& res2)
		return (0);
	else if (neighbour.type == CYLINDER && shdw.t == shdw.dist.t1
		&& (!cylinder_height(&neighbour, shdw.dist.t1,
				shdw.l_ray, shdw.pt_origin)))
		return (1);
	else if (neighbour.type == CYLINDER && t2_limits(shdw.dist.t2, shdw.l_mag)
		&& (!cylinder_height(&neighbour, shdw.dist.t2,
				shdw.l_ray, shdw.pt_origin)))
		return (1);
	return (0);
}
