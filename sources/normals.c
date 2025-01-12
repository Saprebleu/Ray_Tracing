/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:54:37 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/12 19:02:53 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

// Reversed 3D rotation matrix

void	xyz_rot_matrix_reverse(t_vector rotated,
		t_vector *original, t_angles angles)
{
	double	alpha;
	double	beta;
	double	gamma;

	alpha = angles.alpha;
	beta = angles.beta;
	gamma = angles.gamma;
	original->x = ((cos(beta) * cos(gamma)) * rotated.x)
		+ ((cos(beta) * sin(gamma)) * rotated.y)
		+ ((-sin(beta)) * rotated.z);
	original->y = ((sin(alpha) * sin(beta) * cos(gamma)
				- cos(alpha) * sin(gamma)) * rotated.x)
		+ ((sin(alpha) * sin(beta) * sin(gamma)
				+ cos(alpha) * cos(gamma)) * rotated.y)
		+ ((sin(alpha) * cos(beta)) * rotated.z);
	original->z = ((cos(alpha) * sin(beta) * cos(gamma)
				+ sin(alpha) * sin(gamma)) * rotated.x)
		+ ((cos(alpha) * sin(beta) * sin(gamma)
				- sin(alpha) * cos(gamma)) * rotated.y)
		+ ((cos(alpha) * cos(beta)) * rotated.z);
}

static t_vector	rotated_cyl_axis(t_object cylinder)
{
	t_vector	axis;
	t_angles	angles;

	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	find_angles(&angles, cylinder.direction, -1);
	xyz_rot_matrix_reverse(axis, &axis, angles);
	return (axis);
}

void	cylinder_norm(t_fig_info *fig_inf,
		t_vector pt_on_cyl, t_object cylinder)
{
	double		t;
	t_vector	p;
	t_vector	b;
	t_vector	a;
	t_vector	anorm;

	b = rotated_cyl_axis(cylinder);
	a = create_vector(&cylinder.position, &pt_on_cyl);
	anorm = a;
	normalize_vector(&anorm);
	t = magnitude(a) * dot_product(&anorm, &b);
	p.x = cylinder.position.x + (t * b.x);
	p.y = cylinder.position.y + (t * b.y);
	p.z = cylinder.position.z + (t * b.z);
	fig_inf->normal = create_vector(&p, &pt_on_cyl);
	normalize_vector(&fig_inf->normal);
	fig_inf->normal.x *= fig_inf->in_or_out;
	fig_inf->normal.y *= fig_inf->in_or_out;
	fig_inf->normal.z *= fig_inf->in_or_out;
}

void	sphere_norm(t_fig_info *fig_inf, t_object sphere)
{
	t_vector	sphere_norm;

	sphere_norm.x = fig_inf->pt_on_figure.x - sphere.position.x;
	sphere_norm.y = fig_inf->pt_on_figure.y - sphere.position.y;
	sphere_norm.z = fig_inf->pt_on_figure.z - sphere.position.z;
	normalize_vector(&sphere_norm);
	sphere_norm.x *= fig_inf->in_or_out;
	sphere_norm.y *= fig_inf->in_or_out;
	sphere_norm.z *= fig_inf->in_or_out;
	fig_inf->normal = sphere_norm;
}

void	plane_norm(t_fig_info *fig_inf, t_object plane)
{
	t_vector	norm;

	norm.x = plane.direction.x * fig_inf->in_or_out;
	norm.y = plane.direction.y * fig_inf->in_or_out;
	norm.z = plane.direction.z * fig_inf->in_or_out;
	fig_inf->normal = norm;
}
