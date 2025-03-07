#include "lights.h"

// Especially when the shadow
// is cast by a cylinder,
// shadow_data is modified
// (rotated).

static void	init_data(t_sha_data *sd,
			t_lights lights, t_fig_info finfo)
{
	sd->l_ray = lights.lig_ray;
	sd->pt_origin = finfo.pt_on_figure;
	sd->rot_light = finfo.wrld.light_position;
	sd->l_mag = lights.lig_mag;
	sd->dist.t1 = MAXFLOAT;
	sd->dist.t2 = MAXFLOAT;
	sd->t = MAXFLOAT;
}

void	t_n_lmag(t_sha_data *shdw, t_object neighbour)
{
	rotated(&shdw->pt_origin, &shdw->rot_light, neighbour);
	shdw->l_ray = create_vector(&shdw->pt_origin, &shdw->rot_light);
	shdw->l_mag = magnitude(shdw->l_ray);
	normalize_vector(&shdw->l_ray);
	t_for_cylinder(shdw->pt_origin, shdw->l_ray, neighbour, &shdw->dist);
}

static double	t1_or_t2(t_sha_data shdw, t_fig_info finfo,
		t_object figure, t_object neighbour)
{
	double	t;

	if ((inside(finfo.in_or_out) && t1_limits(shdw.dist.t1, shdw.l_mag))
		|| (outside(finfo.in_or_out, figure, neighbour)
			&& t1_limits(shdw.dist.t1, shdw.l_mag)))
		t = shdw.dist.t1;
	else if ((inside(finfo.in_or_out) && t2_limits(shdw.dist.t2, shdw.l_mag))
		|| (outside(finfo.in_or_out, figure, neighbour)
			&& t2_limits(shdw.dist.t2, shdw.l_mag)))
		t = shdw.dist.t2;
	else
		t = MAXFLOAT;
	return (t);
}

static int	shady(t_lights *lights, t_sha_data shdw,
			t_object neighbour)
{
	if (shdw.t != MAXFLOAT)
	{
		if (neighbour.type == CYLINDER
			&& not_cyl_height(shdw, neighbour))
			return (0);
		lights->specular.r = 0;
		lights->specular.g = 0;
		lights->specular.b = 0;
		lights->diffuse.r = 0;
		lights->diffuse.g = 0;
		lights->diffuse.b = 0;
		return (1);
	}
	return (0);
}

// "nghbr"(neighbour) is another
// figure that might be situated btw
// the origin point and the light
// source.
// "lmag" is the magnitude of the
// light ray (that might be rotated).
// "lmag" is the limit for "t".
// In order to figure out whether
// another figure intercepts the
// point-light vector (= casts a shadow)
// we need to determine a "t" distance
// from the origin point to the nghbr
// figure.

void	shadows(t_lights *lights, t_fig_info finfo, t_object figure)
{
	int			j;
	t_sha_data	shdw;
	t_object	nghbr;

	j = -1;
	while (++j < finfo.wrld.nb_objects)
	{
		nghbr = finfo.wrld.objects[j];
		init_data(&shdw, *lights, finfo);
		if ((outside(finfo.in_or_out, figure, nghbr)
				|| inside(finfo.in_or_out)))
		{
			if (nghbr.type == CYLINDER)
				t_n_lmag(&shdw, nghbr);
			else if (nghbr.type == SPHERE)
				t_for_sphere(shdw.pt_origin, shdw.l_ray, &nghbr, &shdw.dist);
			else if (nghbr.type == PLANE)
				t_for_plane(shdw.pt_origin, shdw.l_ray, &nghbr, &shdw.dist);
			shdw.t = t1_or_t2(shdw, finfo, figure, nghbr);
			if (shady(lights, shdw, nghbr))
				break ;
		}
	}
}
