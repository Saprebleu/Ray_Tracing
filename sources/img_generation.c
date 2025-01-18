/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:09:08 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/13 18:28:22 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include <math.h>
#include <stdio.h>

void	set_pixel_color(t_display *display, int x, int y, t_color *color)
{
	if (!display->final)
	{
		display->image_buffer[y * display->size_line
			+ x * display->bits_per_pixel / 8 + 0] = color->b;
		display->image_buffer[y * display->size_line
			+ x * display->bits_per_pixel / 8 + 1] = color->g;
		display->image_buffer[y * display->size_line
			+ x * display->bits_per_pixel / 8 + 2] = color->r;
	}
}

void	intersect_figures(t_vector eye, t_vector pixel,
		t_vector ray, t_world *world)
{
	int	j;

	j = -1;
	while (++j < world->nb_objects)
	{
		world->objects[j].t_min = MAXFLOAT;
		world->objects[j].pt_color = world->objects[j].color;
		if (world->objects[j].type == SPHERE)
			intersect_sphere(pixel, ray, &world->objects[j], *world);
		else if (world->objects[j].type == CYLINDER)
			intesect_cylinder(pixel, eye, &world->objects[j], *world);
		else if (world->objects[j].type == PLANE)
			intersect_plane(pixel, ray, &world->objects[j], *world);
		else
			continue ;
	}
}

void	closest_figure(t_display *display, t_world *world, int x, int y)
{
	int		i;
	int		index_obj;
	double	smallest_tmin;

	i = 0;
	index_obj = -1;
	smallest_tmin = MAXFLOAT;
	while (i < world->nb_objects && !display->final)
	{
		if (world->objects[i].t_min < smallest_tmin)
		{
			index_obj = i;
			smallest_tmin = world->objects[i].t_min;
		}
		i++;
	}
	if (index_obj != -1)
	{
		if (world->objects[index_obj].type == SPHERE
			|| world->objects[index_obj].type == CYLINDER
			|| world->objects[index_obj].type == PLANE)
			set_pixel_color(display, x, y, &world->objects[index_obj].pt_color);
	}
}

// The "ray" starts at the eye, goes through a pixel of the screen
// and might encounter a figure.

void	generate_image(t_display *display, t_world *world)
{
	t_vector	ray;
	t_vector	pixel;
	t_vector	rot_eye;
	int			x;
	int			y;

	display->final = 0;
	initialize_eye(&rot_eye, *world);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			initialize_pixel(&pixel, *world, x, y);
			ray = rotated_cam_ray(&pixel, &rot_eye, *world);
			intersect_figures(rot_eye, pixel, ray, world);
			closest_figure(display, world, x, y);
		}
	}
	display->world = world;
	printf("\n\n   --- End of rendering ---\n");
}
