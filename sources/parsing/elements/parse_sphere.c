/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:01 by tjarross          #+#    #+#             */
/*   Updated: 2025/01/06 16:34:48 by jayzatov         ###   ########.fr       */
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

static int	parse_sphere2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Sphere\n"), -6);
	if (false == is_color(*line_split))
		return (printf("Error\nSphere Color is not a color\n"), -7);
	world->objects[world->nb_objects].color = get_color(*line_split);
	if (false == is_color_in_range(world->objects[world->nb_objects].color,
			0, 255))
		return (printf("Error\nSphere Color not in range [0, 255]\n"), -8);
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -9);
	world->objects[world->nb_objects].type = SPHERE;
	world->nb_objects++;
	return (0);
}

int	parse_sphere(char **line_split, t_world *world)
{
	world->objects = ft_realloc(world->objects,
			sizeof(t_object) * world->nb_objects,
			sizeof(t_object) * (world->nb_objects + 1));
	if (world->objects == NULL)
		return (-1);
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Sphere\n"), -2);
	if (false == is_vector(*line_split))
		return (printf("Error\nSphere Position is not a vector\n"), -3);
	world->objects[world->nb_objects].position = get_vector(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Sphere\n"), -4);
	if (false == is_double(*line_split))
		return (printf("Error\nSphere Diameter is not a double\n"), -5);
	world->objects[world->nb_objects].diameter = get_double(*line_split);
	return (parse_sphere2(line_split, world));
}
