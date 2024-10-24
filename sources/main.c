/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/24 20:15:42 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "mlx.h"

#include "world.h"
#include "parsing.h"

void	print_parsing(t_world world);

void set_pixel_color(t_display *display, int x, int y, int color)
{
	display->image_buffer[y * display->size_line +
		x * display->bits_per_pixel / 8 + 0] = GET_BLUE(color);
	display->image_buffer[y * display->size_line +
		x * display->bits_per_pixel / 8 + 1] = GET_GREEN(color);
	display->image_buffer[y * display->size_line +
		x * display->bits_per_pixel / 8 + 2] = GET_RED(color);
}

bool intersect_sphere(t_vector *camera_position, t_vector *ray, t_object *sphere)
{
	t_vector distance;

	distance.x = sphere->position.x - camera_position->x;
	distance.y = sphere->position.y - camera_position->y;
	distance.z = sphere->position.z - camera_position->z;

	sphere->a = ray->x * ray->x + ray->y * ray->y + ray->z * ray->z;
	sphere->b = 2 * ray->x * distance.x + 2 * ray->y * distance.y + 2 * ray->z * distance.z;
	sphere->c = camera_position->x * camera_position->x + camera_position->y * camera_position->y + camera_position->z * camera_position->z
			+ sphere->position.x * sphere->position.x + sphere->position.y * sphere->position.y + sphere->position.z * sphere->position.z
			- 2 * (distance.x + distance.y + distance.z)
			- (sphere->diameter / 2.0f) * (sphere->diameter / 2.0f);
	sphere->delta = sphere->b * sphere->b - 4 * sphere->a * sphere->c;
	if (sphere->delta >= 0)
	{
		sphere->t1 = (-sphere->b - sqrtf(powf(sphere->b, 2) - 4 * sphere->a * sphere->c)) / (2 * sphere->a);
		sphere->t2 = (-sphere->b + sqrtf(powf(sphere->b, 2) - 4 * sphere->a * sphere->c)) / (2 * sphere->a);
		sphere->t_min = sphere->t1 > sphere->t2 ? sphere->t2 : sphere->t1;
		return (true);
	}
	return (false);
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
	display.mlx_ptr = mlx_init();
	if (display.mlx_ptr == NULL)
		return (printf("Error\nCannot create mlx context\n"), EXIT_FAILURE);
	display.mlx_window = mlx_new_window(display.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
	if (display.mlx_window == NULL)
		return (printf("Error\nCannot create mlx window\n"), EXIT_FAILURE);
	display.mlx_image = mlx_new_image(display.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (display.mlx_image == NULL)
		return (printf("Error\nCannot create mlx image\n"), EXIT_FAILURE);
	display.image_buffer = mlx_get_data_addr(display.mlx_image,
		&display.bits_per_pixel, &display.size_line, &display.endian);
	if (display.image_buffer == NULL)
		return (printf("Error\nCannot get mlx image buffer\n"), EXIT_FAILURE);

	for (int y = 0; y < WINDOW_HEIGHT; y++)
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			t_object sphere =
			{
				.color =
				{
					.r = 255,
					.g = 0,
					.b = 0
				},
				.diameter = 200,
				.position =
				{
					.x = 0,
					.y = 0,
					.z = 0,
				}
			};
			world.camera_position = (t_vector)
			{
				.x = 0,
				.y = 0,
				.z = -1100
			};
			t_vector ray;

			ray.x = world.camera_position.x - (WINDOW_WIDTH / 2.0f) + x;
			ray.y = world.camera_position.y - (WINDOW_HEIGHT / 2.0f) + y;
			ray.z = world.camera_position.z - 1000;

			if (true == intersect_sphere(&world.camera_position, &ray, &sphere))
				set_pixel_color(&display, x, y, GET_RGB(sphere.color.r, sphere.color.g, sphere.color.b));
		}

	mlx_put_image_to_window(display.mlx_ptr, display.mlx_window, display.mlx_image, 0, 0);
	mlx_loop(display.mlx_ptr);
	return (EXIT_SUCCESS);
}
