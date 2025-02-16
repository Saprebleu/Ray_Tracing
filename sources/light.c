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

void	color_is_lit(t_color *color, t_lights lights, t_object figure)
{
	t_light	amb;
	t_light	spec;
	t_light	diff;

	amb = lights.ambient;
	spec = lights.specular;
	diff = lights.diffuse;
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
	t_lights	lights;
	t_lrays		r;
	double		cos_ln;

	r.to_lig = create_vector(&fig_inf.pt_on_figure, &world.light_position);
	lights.lig_mag = magnitude(r.to_lig);
	r.to_eye = create_vector(&fig_inf.pt_on_figure, &pixel);
	normalize_vector(&r.to_lig);
	normalize_vector(&r.to_eye);
	cos_ln = dot_product(&r.to_lig, &fig_inf.normal);
	light_reflection(&r.l_ref, fig_inf, r.to_lig, cos_ln);
	ambient(fig_inf, &lights);
	specular(fig_inf, &lights, r, cos_ln);
	diffuse(fig_inf, &lights, cos_ln);
	lights.lig_ray = r.to_lig;
	if (cos_ln >= 0)
		shadows(&lights, fig_inf, figure);
	color_is_lit(&color, lights, figure);
	return (color);
}
