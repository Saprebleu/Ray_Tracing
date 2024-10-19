/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:46:38 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:46:47 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

bool	is_vector_in_range(t_vector v, float lower, float upper)
{
	return (is_float_in_range(v.x, lower, upper)
		&& is_float_in_range(v.y, lower, upper)
		&& is_float_in_range(v.z, lower, upper));
}

bool	is_vector(const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (++j < 3)
	{
		if (s[i] == '-')
			i++;
		if (1 != ft_isdigit(s[i]))
			return (false);
		while (1 == ft_isdigit(s[i]))
			i++;
		if (s[i] == '.')
		{
			if (1 != ft_isdigit(s[++i]))
				return (false);
			while (1 == ft_isdigit(s[i]))
				i++;
		}
		if (j != 2 && s[i] != ',')
			return (false);
		i++;
	}
	return (s[i - 1] == '\0');
}

t_vector	get_vector(const char *s)
{
	t_vector	v;

	v.x = get_float(s);
	v.y = get_float(ft_strchr(s, ',') + 1);
	v.z = get_float(ft_strchr(ft_strchr(s, ',') + 1, ',') + 1);
	return (v);
}
