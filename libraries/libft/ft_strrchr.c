/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:27:24 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/08 18:01:23 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
// #include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[ft_strlen(s) - i] == (char)c)
			return ((char *)s + ft_strlen(s) - i);
		i++;
	}
	return (NULL);
}
// int main(void)
// {
//     char *res = ft_strrchr("bAnjouAr", 'v');
//     if(res == NULL)
//         printf("%s\n", "NULL");
//     else
//         printf("%s\n", res);
//     return (0);
// }
