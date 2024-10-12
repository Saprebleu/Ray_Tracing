/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:22:13 by jayzatov          #+#    #+#             */
/*   Updated: 2024/02/18 15:24:57 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup2(char *s);
char	*ft_strlcpy2(char *dst, const char *src, size_t size);
size_t	ft_strlen2(const char *s);

int	has_n(const char *s)
{
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

char	*create_to_print_and_temp2(char **temp, char **temp2, char **buffer)
{
	char	*to_print;

	to_print = malloc(sizeof(char) * (n_is_nth_char_of(*temp) + 1));
	to_print = ft_strlcpy2(to_print, *temp, n_is_nth_char_of(*temp));
	to_print[n_is_nth_char_of(*temp)] = '\0';
	*temp2 = begins_after_n(*temp);
	free(*temp);
	*temp = *temp2;
	if (**temp == '\0')
	{
		free(*temp);
		*temp = NULL;
	}
	free(*buffer);
	return (to_print);
}

char	*return_the_line_or_null(char **temp, char **to_print, char **buffer,
								ssize_t read_result)
{
	if (*temp != NULL && read_result == 0)
	{
		*to_print = ft_strdup2(*temp);
		free(*temp);
		*temp = NULL;
		free(*buffer);
		return (*to_print);
	}
	if (*temp == NULL && read_result == 0)
		free(*buffer);
	return (NULL);
}

char	*realloc_and_concat(char **temp, char *buffer, size_t nbr_chars_temp,
							size_t nbr_chars_to_add)
{
	char	*third_string;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	if (*temp == NULL && nbr_chars_to_add <= 0)
		return (NULL);
	third_string = (char *)malloc((nbr_chars_temp + nbr_chars_to_add + 1)
			* sizeof(char));
	if (third_string == NULL)
		return (NULL);
	while (++i < nbr_chars_temp && *temp != NULL)
		third_string[i] = (*temp)[i];
	while (i < (nbr_chars_temp + nbr_chars_to_add))
	{
		third_string[i] = buffer[j];
		i++;
		j++;
	}
	free(*temp);
	third_string[nbr_chars_temp + nbr_chars_to_add] = '\0';
	*temp = third_string;
	return (third_string);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*temp;
	char		*to_print;
	ssize_t		read_result;
	char		*temp2;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	read_result = read(fd, buffer, BUFFER_SIZE);
	while (read_result >= 0)
	{
		realloc_and_concat(&temp, buffer, ft_strlen2(temp), read_result);
		if (has_n(temp))
		{
			to_print = create_to_print_and_temp2(&temp, &temp2, &buffer);
			return (to_print);
		}
		if (read_result == 0 || read_result == -1)
			return (return_the_line_or_null(&temp, &to_print,
					&buffer, read_result));
		read_result = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (NULL);
}
