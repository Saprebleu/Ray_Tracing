/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:26:03 by jayzatov          #+#    #+#             */
/*   Updated: 2023/11/07 17:29:21 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
// #include <stdio.h>
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
// int main(void)
// {
//     printf("%d\n", ft_isascii(-2));
//     printf("%d\n", isascii(-2));
//     printf("%d\n", ft_isascii(4));
//     printf("%d\n", isascii(4));

//     return (0);
// }
