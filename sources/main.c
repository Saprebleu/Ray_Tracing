/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/15 11:29:07 by jayzatov         ###   ########.fr       */
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

// "Camera distance" is calculated thanks to the TOA formula of a right triangle,
// 	knowing fov degrees (converted to radians for tanf()) and screen width.
//  It is the eye-camera distance;

// The "ray" starts at the eye, goes through a pixel of the screen
// and might encounter a figure.

void	generate_image(t_display *display, t_world *world)
{
	t_vector	ray;
	t_vector	pixel;
	t_vector	eye;
	int			x;
	int			y;
	float		camera_distance;

	camera_distance = ((WINDOW_WIDTH / 2.0f)
						/ tanf((world->camera_fov / 2.0f) * M_PI / 180.0f));
	pixel.z = world->camera_position.z;
	eye.x = world->camera_position.x;
	eye.y = world->camera_position.y;
	eye.z = world->camera_position.z - camera_distance;
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			pixel.x = world->camera_position.x + (WINDOW_WIDTH / 2.0f) - x;
			pixel.y = world->camera_position.y - (WINDOW_HEIGHT / 2.0f) + y;
			ray = create_vector(&eye, &pixel);
			normalize_vector(&ray);

			int j = -1;
			while (++j < world->nb_objects)
			{
				world->objects[j].t_min = MAXFLOAT;
				if (world->objects[j].type == SPHERE)
					intersect_sphere(&pixel, &ray, &world->objects[j]);
				else if (world->objects[j].type == CYLINDER)
					intesect_cylinder(eye, pixel, &world->objects[j]);
				else if (world->objects[j].type == PLANE)
					intersect_plane(pixel, &ray, &world->objects[j]);
			}
			
			int i = 0;
			int index_obj = -1;
			float smallest_tmin = MAXFLOAT;
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
				set_pixel_color(display, x, y, &world->objects[index_obj].color);

		}
	}
}

bool	initialize_mlx_context(t_display *display, int window_width,
	int window_height, char *window_title)
{
	
	ft_memset(display, 0, sizeof(*display));
	display->mlx_ptr = mlx_init();
	if (display->mlx_ptr == NULL)
		return (printf("Error\nCannot create mlx context\n"), false);
	display->mlx_window = mlx_new_window(display->mlx_ptr, window_width,
			window_height, window_title);
	if (display->mlx_window == NULL)
		return (printf("Error\nCannot create mlx window\n"), false);
	display->mlx_image = mlx_new_image(display->mlx_ptr, window_width,
			window_height);
	if (display->mlx_image == NULL)
		return (printf("Error\nCannot create mlx image\n"), false);
	display->image_buffer = mlx_get_data_addr(display->mlx_image,
			&display->bits_per_pixel, &display->size_line, &display->endian);
	if (display->image_buffer == NULL)
		return (printf("Error\nCannot get mlx image buffer\n"), false);
	return (true);
}

void	clean_mlx_context(t_display *display)
{
	if (display->mlx_image != NULL)
	{
		mlx_destroy_image(display->mlx_ptr, display->mlx_image);
		display->mlx_image = NULL;
	}
	if (display->mlx_window != NULL)
	{
		mlx_destroy_window(display->mlx_ptr, display->mlx_window);
		display->mlx_window = NULL;
	}
	if (display->mlx_ptr != NULL)
	{
		mlx_destroy_display(display->mlx_ptr);
		free(display->mlx_ptr);
		display->mlx_ptr = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_display	display;
	t_world		world;
	int			parsing_ret;

	if (argc != 2)
		return (printf("Error\nProgram take only one argument\n"),
			EXIT_FAILURE);
	parsing_ret = parse_rt(argv[1], &world);
	if (parsing_ret != 0)
		return (EXIT_FAILURE);
	print_parsing(world);
	if (false == initialize_mlx_context(&display, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE))
		return (clean_mlx_context(&display), EXIT_FAILURE);
	generate_image(&display, &world);
	mlx_put_image_to_window(display.mlx_ptr, display.mlx_window,
		display.mlx_image, 0, 0);
	mlx_loop(display.mlx_ptr);
	clean_mlx_context(&display);
	free(world.objects);
	return (EXIT_SUCCESS);
}
