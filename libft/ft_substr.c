/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:06:40 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/08 18:11:13 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*after_verification_substr(char const *s,
									unsigned int start, size_t len)
{
	char	*resu;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
	{
		resu = (char *)malloc(sizeof(char) * 1);
		if (resu == NULL)
			return (NULL);
		resu[0] = '\0';
		return (resu);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	resu = (char *)malloc(sizeof(char) * (len + 1));
	if (resu == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		resu[i] = s[start];
		i++;
		start++;
	}
	resu[i] = '\0';
	return (resu);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	else
		return (after_verification_substr(s, start, len));
}
// int main(void)
// {
//     // printf("%s\n", ft_substr("abcdefghij", 18, 19));
//     char * str = ft_strdup("0123456789");
// 	char * s = ft_substr(str, 9, 10);
//     printf("%s\n", s);
//     printf("%d\n", 2);
//     return(0);
// }
