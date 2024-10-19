/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:39:27 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:46:31 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "parsing/parsing_utils.h"
#include "world.h"

bool	is_color_in_range(t_color c, int lower, int upper)
{
	return (is_int_in_range(c.r, lower, upper)
		&& is_int_in_range(c.g, lower, upper)
		&& is_int_in_range(c.b, lower, upper));
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

t_color	get_color(const char *s)
{
	t_color	c;

	c.r = ft_atoi(s);
	c.g = ft_atoi(ft_strchr(s, ',') + 1);
	c.b = ft_atoi(ft_strchr(ft_strchr(s, ',') + 1, ',') + 1);
	return (c);
}
