#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "libft.h"
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
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (true);
	if (s[i] != '.')
        return (false);
    i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
    return (s[i] == '\0');
}

bool	is_int(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	return (s[i] == '\0');
}

bool	is_float_in_range(float n, float lower, float upper)
{
	return (n >= lower && n <= upper);
}

bool	is_int_in_range(int n, int lower, int upper)
{
	return (n >= lower && n <= upper);
}

bool	is_vector_in_range(t_vector v, float lower, float upper)
{
	return (is_float_in_range(v.x, lower, upper)
		&& is_float_in_range(v.y, lower, upper)
		&& is_float_in_range(v.z, lower, upper));
}

bool	is_color_in_range(t_color c, int lower, int upper)
{
	return (is_int_in_range(c.r, lower, upper)
		&& is_int_in_range(c.g, lower, upper)
		&& is_int_in_range(c.b, lower, upper));
}

bool	is_vector(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (true);
	if (s[i] != '.')
        return (false);
    i++;
	if (1 != ft_isdigit(s[i]))
		return (false);
	while (1 == ft_isdigit(s[i]))
		i++;
    return (s[i] == '\0');
}

bool	is_color(const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (s[i] == '-')
			i++;
		if (1 != ft_isdigit(s[i]))
			return (false);
		while (1 == ft_isdigit(s[i]))
			i++;
		if (j != 2 && s[i] != ',')
			return (false);
        i++;
		j++;
	}
	return (s[i - 1] == '\0');
}

t_vector	get_vector(const char *s)
{
	(void)s;
	return ((t_vector){0.0f, 0.0f, 0.0f});
}

t_color	get_color(const char *s)
{
	(void)s;
	return ((t_color){0, 0, 0});
}

float	get_float(const char *s)
{
	int		i;
	float	n;
	float	decimals;
	int		decimal_factor;
	char	*decimal_str;

	n = ft_atoi(s);
	decimals = 0;
	decimal_factor = 1;
	decimal_str = ft_strchr(s, '.');
	if (decimal_str == NULL)
		return (n);
	decimals = ft_atoi(decimal_str + 1);
	return (n + (decimals / (float)powf(10, ft_strlen(decimal_str + 1))));
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
