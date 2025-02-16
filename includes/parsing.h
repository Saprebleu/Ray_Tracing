#ifndef PARSING_H
# define PARSING_H

# include "world.h"

int	parse_cylinder(char **line_split, t_world *world);
int	parse_plane(char **line_split, t_world *world);
int	parse_sphere(char **line_split, t_world *world);
int	parse_light(char **line_split, t_world *world);
int	parse_camera(char **line_split, t_world *world);
int	parse_ambient(char **line_split, t_world *world);
int	parse_rt(const char *pathname, t_world *world);

#endif