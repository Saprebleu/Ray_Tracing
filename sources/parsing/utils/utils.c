/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:43:51 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:45:30 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (free(ptr), printf("Error\n%s\n", strerror(errno)), NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

char	**goto_next_value(char **line_split)
{
	while (*line_split != NULL)
	{
		if ((*line_split)[0] != '\0')
			return (line_split);
		line_split++;
	}
	return (NULL);
}
