/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_generation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:09:08 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/27 11:38:07 by jayzatov         ###   ########.fr       */
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

void	set_pixel_color(t_display *display, int x, int y, const t_color *color)
{
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 0] = color->b;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 1] = color->g;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 2] = color->r;
}

void	put_shadows(t_display *display, t_world *world, int x, int y, t_vector pixel,
		t_vector ray)
{
	(void)display;
	(void)x;
	(void)y;
	(void)ray;
	(void)pixel;
	int		i;
	
	i = 0;
	while(i < world->nb_objects)
	{
		if (world->objects[i].t_min < MAXFLOAT)
		{
			world->objects[i].pt_color = shadow_on_figure(world->objects[i].t_min, world->objects[i], *world, -1, pixel, ray);
			set_pixel_color(display, x, y, &world->objects[i].pt_color);
		}
		i++;
	}
}

void	intersect_figures(t_vector eye, t_vector pixel, t_vector ray, t_world *world)
{
	int j = -1;
	while (++j < world->nb_objects)
	{
		world->objects[j].t_min = MAXFLOAT;
		if (world->objects[j].type == SPHERE)
			intersect_sphere(&pixel, &ray, &world->objects[j], *world);
		else if (world->objects[j].type == CYLINDER)
			intesect_cylinder(eye, pixel, &world->objects[j], *world);
		else if (world->objects[j].type == PLANE)
			intersect_plane(pixel, &ray, &world->objects[j]);
	}
}

void	closest_figure(t_display *display, t_world *world, int x, int y)
{
	int		i;
	int		index_obj;
	float	smallest_tmin;
	
	i = 0;
	index_obj = -1;
	smallest_tmin = MAXFLOAT;
	while(i < world->nb_objects)
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
			|| world->objects[index_obj].type == CYLINDER)
		{
			set_pixel_color(display, x, y, &world->objects[index_obj].pt_color);	
			printf("closest pixel\n");
		}
		else
			set_pixel_color(display, x, y, &world->objects[index_obj].color);	
	}
}

// The "ray" starts at the eye, goes through a pixel of the screen
// and might encounter a figure.

void	generate_image(t_display *display, t_world *world)
{
	t_vector	ray;
	t_vector	pixel;
	t_vector	eye;
	int			x;
	int			y;
	
	initialize_eye(&eye, *world);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			initialize_pixel(&pixel, *world, x, y);
			ray = rotated_cam_ray(&pixel, &eye, *world);
			// put_shadows(display, world, x, y, pixel, ray);
			
			intersect_figures(eye, pixel, ray, world);
			
			closest_figure(display, world, x, y);
		}
	}
}