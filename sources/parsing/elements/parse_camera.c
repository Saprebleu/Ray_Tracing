#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "parsing/utils.h"
#include "world.h"

int	parse_camera(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -1);
	if (false == is_vector(*line_split))
		return (printf("Error\nCamera Position is not a vector\n"), -2);
	world->camera_position = get_vector(*line_split);
	if (false == is_vector_in_range(world->camera_position, 0.0f, 1.0f))
		return (printf("Error\nCamera Position not in range [0, 1]\n"), -3);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -4);
	if (false == is_vector(*line_split))
		return (printf("Error\nCamera Direction is not a vector\n"), -5);
	world->camera_direction = get_vector(*line_split);
	if (false == is_vector_in_range(world->camera_direction, 0.0f, 1.0f))
		return (printf("Error\nCamera Direction not in range [0, 1]\n"), -6);
	line_split = goto_next_value(line_split + 1);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Camera\n"), -7);
	if (false == is_int(*line_split))
		return (printf("Error\nCamera Fov is not an integer\n"), -8);
	world->camera_fov = ft_atoi(*line_split);
	if (false == is_int_in_range(world->camera_fov, 0, 180))
		return (printf("Error\nCamera Fov not in range [0, 180]\n"), -9);
	line_split = goto_next_value(line_split + 1);
	if (line_split != NULL)
		return (printf("Error\nInvalid value: '%s'\n", *line_split), -10);
	world->has_camera = true;
	return (0);
}
