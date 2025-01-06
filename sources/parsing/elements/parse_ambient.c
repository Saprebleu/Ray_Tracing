/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:28:51 by tjarross          #+#    #+#             */
/*   Updated: 2025/01/06 16:41:41 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

int	parse_ambient(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Ambient\n"), -1);
	if (false == is_double(*line_split))
		return (printf("Error\nAmbient Power is not a double\n"), -2);
	world->ambient_power = atof(*line_split);
	if (false == is_double_in_range(world->ambient_power, 0.0, 1.0))
		return (printf("Error\nAmbient Power not in range [0, 1]\n"), -3);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Ambient\n"), -4);
	if (false == is_color(*line_split))
		return (printf("Error\nAmbient Color is not a color\n"), -5);
	world->ambient_color = get_color(*line_split);
	if (false == is_color_in_range(world->ambient_color, 0, 255))
		return (printf("Error\nAmbient Color not in range [0, 255]\n"), -6);
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -7);
	world->has_ambient = true;
	return (0);
}
