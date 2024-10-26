/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/26 19:33:49 by tjarross         ###   ########.fr       */
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

void	print_parsing(t_world world);

void	set_pixel_color(t_display *display, int x, int y, const t_color *color)
{
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 0] = color->b;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 1] = color->g;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 2] = color->r;
}

float	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	create_vector(const t_vector *start, const t_vector *end)
{
	t_vector	v;

	v.x = end->x - start->x;
	v.y = end->y - start->y;
	v.z = end->z - start->z;
	return (v);
}

float	solve_polynom(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4 * a * c;
	if (delta == 0.0f)
		return (-b / (2.0f * a));
	else if (delta > 0.0f)
	{
		t1 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		t2 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		return (fminf(t1, t2));
	}
	return (-1.0f);
}

bool	intersect_sphere(const t_vector *camera_position,
	const t_vector *ray, t_object *sphere)
{
	t_vector	distance;
	float		a;
	float		b;
	float		c;

	distance = create_vector(&sphere->position, camera_position);
	a = dot_product(ray, ray);
	b = 2.0f * dot_product(ray, &distance);
	c = dot_product(&distance, &distance)
		- ((sphere->diameter / 2.0f) * (sphere->diameter / 2.0f));
	sphere->t_min = solve_polynom(a, b, c);
	return (sphere->t_min != -1.0f);
}

void	generate_image(t_display *display, t_world *world)
{
	t_vector	ray;
	t_vector	pixel;
	int			x;
	int			y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			pixel.x = world->camera_position.x - (WINDOW_WIDTH / 2.0f) + x;
			pixel.y = world->camera_position.y + (WINDOW_HEIGHT / 2.0f) - y;
			pixel.z = world->camera_position.z;
			ray.x = pixel.x - world->camera_position.x;
			ray.y = pixel.y - world->camera_position.y;
			ray.z = pixel.z - (world->camera_position.z
					+ ((WINDOW_WIDTH / 2.0f)
						/ tanf((world->camera_fov / 2.0f) * M_PI / 180.0f)));
			if (true == intersect_sphere(&world->camera_position, &ray,
					&world->objects[0]))
				set_pixel_color(display, x, y, &world->objects[0].color);
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
