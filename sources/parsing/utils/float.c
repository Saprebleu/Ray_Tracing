/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:31:17 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/04 20:18:44 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#include "libft.h"

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

bool	is_float_in_range(float n, float lower, float upper)
{
	return (fmaxf(n, lower) == n && fminf(n, upper) == n);
}

int	ft_strclen(const char *s, char c)
{
	char	*tmp;

	tmp = ft_strchr(s, c);
	if (tmp == NULL)
		return (ft_strlen(s));
	return (tmp - s);
}

float	get_float(const char *s)
{
	int		sign;
	float	n;
	float	decimals;
	int		i;

	sign = 1;
	if (s[0] == '-')
		sign = -1;
	n = ft_atoi(s);
	decimals = 0;
	i = 0;
	while (s[i] && (ft_isdigit(s[i]) == 1 || s[i] == '-'))
	{
		if (s[i] == '.')
			break ;
		i++;
	}
	if (s[i] != '.')
		return (n);
	decimals = ft_atoi(s + i + 1);
	return (n + (sign
			* (decimals / (float)powf(10, ft_strclen(s + i + 1, ',')))));
}
