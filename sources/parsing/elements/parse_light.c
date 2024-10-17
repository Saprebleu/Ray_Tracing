#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "parsing/utils.h"
#include "world.h"

int	parse_light(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -1);
	if (false == is_vector(*line_split))
		return (printf("Error\nLight Position is not a vector\n"), -2);
	world->light_position = get_vector(*line_split);
	if (false == is_vector_in_range(world->light_position, 0.0f, 1.0f))
		return (printf("Error\nLight Position not in range [0, 1]\n"), -3);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -4);
	if (false == is_float(*line_split))
		return (printf("Error\nLight Power is not a float\n"), -5);
	world->light_power = get_float(*line_split);
	if (false == is_float_in_range(world->light_power, 0.0f, 1.0f))
		return (printf("Error\nLight Power not in range [0, 1]\n"), -6);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -7);
	if (false == is_color(*line_split))
		return (printf("Error\nLight Fov is not an integer\n"), -8);
	world->light_color = get_color(*line_split);
	if (false == is_color_in_range(world->light_color, 0, 255))
		return (printf("Error\nLight Fov not in range [0, 255]\n"), -9);
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -10);
	world->has_camera = true;
	return (0);
}
