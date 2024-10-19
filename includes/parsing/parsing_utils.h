/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:37:01 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/19 14:37:59 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stddef.h>

# include "world.h"

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		**goto_next_value(char **line_split);

bool		is_float(const char *s);
bool		is_float_in_range(float n, float lower, float upper);
float		get_float(const char *s);

bool		is_int(const char *s);
bool		is_int_in_range(int n, int lower, int upper);

bool		is_vector(const char *s);
bool		is_vector_in_range(t_vector v, float lower, float upper);
t_vector	get_vector(const char *s);

bool		is_color(const char *s);
bool		is_color_in_range(t_color c, int lower, int upper);
t_color		get_color(const char *s);

#endif