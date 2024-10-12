/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:54:26 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/08 10:56:59 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}
// int main(void)
// {
//     char *res = ft_strchr("bAnjour", '\0');
//     if(res == NULL)
//         printf("%s\n", "NULL");
//     else
//         printf("%s\n", res);
//     return (0);
// }
