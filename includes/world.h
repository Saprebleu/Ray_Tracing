/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:48:55 by tjarross          #+#    #+#             */
/*   Updated: 2024/10/24 20:04:09 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stdbool.h>

# define WINDOW_TITLE	"miniRT"
# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	768

# define GET_RED(color) ((color & 0xFF0000) >> 16)
# define GET_GREEN(color) ((color & 0x00FF00) >> 8)
# define GET_BLUE(color) ((color & 0x0000FF))
# define GET_RGB(r, g, b) (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b) & 0xFF))

typedef enum e_object_type
{
	NONE = 0,
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3
}	t_object_type;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_object
{
	t_object_type	type;
	t_vector		position;
	t_vector		direction;
	float			diameter;
	float			height;
	t_color			color;
	float			a;
	float			b;
	float			c;
	float			delta;
	float			t1;
	float			t2;
	float			t_min;
}	t_object;

typedef struct s_world
{
	bool		has_ambient;
	t_color		ambient_color;
	float		ambient_power;
	bool		has_camera;
	t_vector	camera_position;
	t_vector	camera_direction;
	int			camera_fov;
	bool		has_light;
	t_vector	light_position;
	t_color		light_color;
	float		light_power;
	int			nb_objects;
	t_object	*objects;
}	t_world;

typedef struct s_display
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*mlx_image;
	char	*image_buffer;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_display;

#endif