/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:18:03 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/07 18:20:41 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cpy;
	size_t	i;

	cpy = (char *)s;
	i = 0;
	while (i < n)
	{
		if (cpy[i] == (char)c)
			return ((char *)cpy + i);
		i++;
	}
	return (NULL);
}
// int main(void)
// {
//     char *res = memchr("AzzzzA", 'A', 1);
//     if(res == NULL)
//         printf("%s\n", "NULL");
//     else
//         printf("%s\n", res);
//     return(0);
// }
