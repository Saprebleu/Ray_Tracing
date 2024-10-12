/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:29:44 by jayzatov          #+#    #+#             */
/*   Updated: 2024/02/18 15:32:56 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

char	*begins_after_n(char *s);
int		n_is_nth_char_of(char *str);
char	*get_next_line(int fd);

#endif
