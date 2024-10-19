/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:40:49 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:46:58 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libft.h"

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

bool	is_int_in_range(int n, int lower, int upper)
{
	return (n >= lower && n <= upper);
}
