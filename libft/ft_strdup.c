/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:59:19 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/08 11:00:14 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t ft_strlen(const char *s)
// {
//     size_t length;
//     length = 0;
//     while(*s)
//     {
//         length++;
//         s++;
//     }
//     return (length);
// }

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (cpy == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
// int main(void)
// {
//     char *truc = ft_strdup("abc");
//     truc[0] = 'P';
//     printf("%s\n", truc);
//     return (0);
// }
