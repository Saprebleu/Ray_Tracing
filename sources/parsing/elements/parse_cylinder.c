/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:03 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:43:17 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

static int	parse_cylinder3(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -10);
	world->objects[world->nb_objects].type = CYLINDER;
	world->nb_objects++;
	return (0);
}

static int	parse_cylinder2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Cylinder\n"), -4);
	if (false == is_float(*line_split))
		return (printf("Error\nCylinder Diameter is not a float\n"), -5);
	world->objects[world->nb_objects].diameter = get_float(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Cylinder\n"), -4);
	if (false == is_float(*line_split))
		return (printf("Error\nCylinder Height is not a float\n"), -5);
	world->objects[world->nb_objects].height = get_float(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Cylinder\n"), -7);
	if (false == is_color(*line_split))
		return (printf("Error\nCylinder Color is not a color\n"), -8);
	world->objects[world->nb_objects].color = get_color(*line_split);
	if (false == is_color_in_range(world->objects[world->nb_objects].color,
			0, 255))
		return (printf("Error\nCylinder Color not in range [0, 255]\n"), -9);
	return (parse_cylinder3(line_split, world));
}

int	parse_cylinder(char **line_split, t_world *world)
{
	world->objects = ft_realloc(world->objects,
			sizeof(t_object) * world->nb_objects,
			sizeof(t_object) * (world->nb_objects + 1));
	if (world->objects == NULL)
		return (-1);
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Cylinder\n"), -2);
	if (false == is_vector(*line_split))
		return (printf("Error\nCylinder Position is not a vector\n"), -3);
	world->objects[world->nb_objects].position = get_vector(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Cylinder\n"), -4);
	if (false == is_vector(*line_split))
		return (printf("Error\nCylinder Direction is not a vector\n"), -5);
	world->objects[world->nb_objects].direction = get_vector(*line_split);
	if (false == is_vector_in_range(world->objects[world->nb_objects].direction,
			-1.0f, 1.0f))
		return (printf("Error\nCylinder Direction not in range [-1, 1]\n"), -6);
	return (parse_cylinder2(line_split, world));
}
