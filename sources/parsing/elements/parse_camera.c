/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:47 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:42:51 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

static int	parse_camera2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -10);
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
	if (false == is_vector_in_range(world->camera_direction, -1.0f, 1.0f))
		return (printf("Error\nCamera Direction not in range [-1, 1]\n"), -6);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -7);
	if (false == is_int(*line_split))
		return (printf("Error\nCamera Fov is not an integer\n"), -8);
	world->camera_fov = ft_atoi(*line_split);
	if (false == is_int_in_range(world->camera_fov, 0, 180))
		return (printf("Error\nCamera Fov not in range [0, 180]\n"), -9);
	return (parse_camera2(line_split, world));
}
