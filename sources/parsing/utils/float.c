/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:31:17 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:34:22 by tjarross         ###   ########.fr       */
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
	return (n >= lower && n <= upper);
}

float	get_float(const char *s)
{
	float	n;
	float	decimals;
	char	*decimal_str;

	n = ft_atoi(s);
	decimals = 0;
	decimal_str = ft_strchr(s, '.');
	if (decimal_str == NULL)
		return (n);
	decimals = ft_atoi(decimal_str + 1);
	return (n + (decimals / (float)powf(10, ft_strlen(decimal_str + 1))));
}
