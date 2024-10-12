/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:45:15 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/07 18:45:19 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

void	ft_putstr_fd(char *s, int fd)
{
	int	length;

	if (s == NULL || fd < 0)
		return ;
	length = (int)ft_strlen(s);
	write(fd, s, length);
}
// int main(void)
// {
//     char s[] = "abc\0";
//     ft_putstr_fd(s, 1);
//     return (0);
// }
