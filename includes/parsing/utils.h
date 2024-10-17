#ifndef UTILS_H
# define UTILS_H

#include "world.h"

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