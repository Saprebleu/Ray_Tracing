/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:47 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/17 18:35:50 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

static int	parse_camera2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -8);
	if (false == is_int(*line_split))
		return (printf("Error\nCamera Fov is not an integer\n"), -9);
	world->camera_fov = ft_atoi(*line_split);
	if (false == is_int_in_range(world->camera_fov, 0, 180))
		return (printf("Error\nCamera Fov not in range [0, 180]\n"), -10);
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -11);
	world->has_camera = true;
	return (0);
}

int	parse_camera(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -1);
	if (false == is_vector(*line_split))
		return (printf("Error\nCamera Position is not a vector\n"), -2);
	world->camera_position = get_vector(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -4);
	if (false == is_vector(*line_split))
		return (printf("Error\nCamera Direction is not a vector\n"), -5);
	world->camera_direction = get_vector(*line_split);
	// if (fabsf(powf(world->camera_direction.x, 2)
	// 		+ powf(world->camera_direction.y, 2)
	// 		+ powf(world->camera_direction.z, 2) - 1.0f) > 0.01f)
	// 	return (printf("Error\nCamera Direction not normalized\n"), -6);
	if (false == is_vector_in_range(world->camera_direction, -1.0f, 1.0f))
		return (printf("Error\nCamera Direction not in range [-1, 1]\n"), -7);
	return (parse_camera2(line_split, world));
}
