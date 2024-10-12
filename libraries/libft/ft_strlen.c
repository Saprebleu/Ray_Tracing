/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:12:48 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/08 12:13:34 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include <string.h>

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s)
	{
		length++;
		s++;
	}
	return (length);
}
// int main(void)
// {
//     printf("%ld\n", ft_strlen("abc"));
//     printf("%ld\n", strlen("abc"));
//     printf("%ld\n", ft_strlen(""));
//     printf("%ld\n", strlen(""));
//     return (0);
// }
