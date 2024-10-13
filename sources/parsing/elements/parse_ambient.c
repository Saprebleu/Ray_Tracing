#include <stddef.h>
#include <stdio.h>

#include "world.h"

char	**goto_next_value(char **line_split)
{
	if (*line_split == NULL)
		return (NULL);
	while (*line_split != NULL)
	{
		if ((*line_split)[0] != '\0')
			return (line_split);
		line_split++;
	}
	return (NULL);
}

bool	is_float(const char *s)
{
	(void)s;
	return (true);
}

bool	is_float_in_range(float n, float lower, float upper)
{
	(void)n; (void)lower; (void)upper;
	return (true);
}

bool	is_int_in_range(int n, int lower, int upper)
{
	(void)n; (void)lower; (void)upper;
	return (true);
}

bool	is_vector_in_range(t_vector v, float lower, float upper)
{
	(void)v; (void)lower; (void)upper;
	return (true);
}

bool	is_color_in_range(t_color c, int lower, int upper)
{
	(void)c; (void)lower; (void)upper;
	return (true);
}

bool	is_vector(const char *s)
{
	(void)s;
	return (true);
}

t_vector	get_vector(const char *s)
{
	(void)s;
	return ((t_vector){0.0f, 0.0f, 0.0f});
}

bool	is_color(const char *s)
{
	(void)s;
	return (true);
}

t_color	get_color(const char *s)
{
	(void)s;
	return ((t_color){0, 0, 0});
}

float	atof(const char *s)
{
	(void)s;
	return (0.0f);
}

int	parse_ambient(char **line_split, t_world *world)
{
	line_split = goto_next_value(line_split);
	if (line_split == NULL)
		return (printf("Error\nNot enough information for Ambient\n"), -1);
	if (false == is_float(*line_split))
		return (printf("Error\nAmbient Power is not a float\n"), -2);
	world->ambient_power = atof(*line_split);
	if (false == is_float_in_range(world->ambient_power, 0.0f, 1.0f))
		return (printf("Error\nAmbient Power not in range [0.0f, 1.0f]\n"), -3);
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
