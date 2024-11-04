/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:58 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/04 20:14:26 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

static int	parse_plane3(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -11);
	world->objects[world->nb_objects].type = PLANE;
	world->nb_objects++;
	return (0);
}

static int	parse_plane2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Plane\n"), -4);
	if (false == is_vector(*line_split))
		return (printf("Error\nPlane Direction is not a vector\n"), -5);
	world->objects[world->nb_objects].direction = get_vector(*line_split);
	if (false == is_vector_in_range(world->objects[world->nb_objects].direction,
			-1.0f, 1.0f))
		return (printf("Error\nPlane Direction not in range [-1, 1]\n"), -6);
	if (fabsf(powf(world->objects[world->nb_objects].direction.x, 2)
			+ powf(world->objects[world->nb_objects].direction.y, 2)
			+ powf(world->objects[world->nb_objects].direction.z, 2) - 1.0f)
		> 0.01f)
		return (printf("Error\nPlane Direction not normalized\n"), -7);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Plane\n"), -8);
	if (false == is_color(*line_split))
		return (printf("Error\nPlane Color is not a color\n"), -9);
	world->objects[world->nb_objects].color = get_color(*line_split);
	if (false == is_color_in_range(world->objects[world->nb_objects].color,
			0, 255))
		return (printf("Error\nPlane Color not in range [0, 255]\n"), -10);
	return (parse_plane3(line_split, world));
}

int	parse_plane(char **line_split, t_world *world)
{
	world->objects = ft_realloc(world->objects,
			sizeof(t_object) * world->nb_objects,
			sizeof(t_object) * (world->nb_objects + 1));
	if (world->objects == NULL)
		return (-1);
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Plane\n"), -2);
	if (false == is_vector(*line_split))
		return (printf("Error\nPlane Position is not a vector\n"), -3);
	world->objects[world->nb_objects].position = get_vector(*line_split);
	return (parse_plane2(line_split, world));
}
