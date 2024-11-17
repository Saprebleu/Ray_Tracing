/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/17 19:10:05 by jayzatov         ###   ########.fr       */
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
