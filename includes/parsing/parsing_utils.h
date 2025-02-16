#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stddef.h>

# include "world.h"

void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		**goto_next_value(char **line_split);

bool		is_double(const char *s);
bool		is_double_in_range(double n, double lower, double upper);
double		get_double(const char *s);

bool		is_int(const char *s);
bool		is_int_in_range(int n, int lower, int upper);

bool		is_vector(const char *s);
bool		is_vector_in_range(t_vector v, double lower, double upper);
t_vector	get_vector(const char *s);

bool		is_color(const char *s);
bool		is_color_in_range(t_color c, int lower, int upper);
t_color		get_color(const char *s);

#endif