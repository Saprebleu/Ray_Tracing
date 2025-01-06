/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:54 by tjarross          #+#    #+#             */
/*   Updated: 2025/01/06 17:10:30 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "parsing/parsing_utils.h"
#include "world.h"

static int	parse_light2(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -10);
	world->has_light = true;
	return (0);
}

int	parse_light(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Light\n"), -1);
	if (false == is_vector(*line_split))
		return (printf("Error\nLight Position is not a vector\n"), -2);
	world->light_position = get_vector(*line_split);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Light\n"), -4);
	if (false == is_double(*line_split))
		return (printf("Error\nLight Power is not a double\n"), -5);
	world->light_power = get_double(*line_split);
	if (false == is_double_in_range(world->light_power, 0.0, 1.0))
		return (printf("Error\nLight Power not in range [0, 1]\n"), -6);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Light\n"), -7);
	if (false == is_color(*line_split))
		return (printf("Error\nLight Color is not a color\n"), -8);
	world->light_color = get_color(*line_split);
	if (false == is_color_in_range(world->light_color, 0, 255))
		return (printf("Error\nLight Color not in range [0, 255]\n"), -9);
	return (parse_light2(line_split, world));
}
