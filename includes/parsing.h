#ifndef PARSING_H
#define PARSING_H

#include "world.h"

int	parse_ambient(char **line_split, t_world *world);
int	parse_rt(const char *pathname, t_world *world);



void print_parsing(t_world world);

#endif