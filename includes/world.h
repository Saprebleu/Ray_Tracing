/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:48:55 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/17 19:09:58 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include <stdbool.h>

# define WINDOW_TITLE	"miniRT"
# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	768

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

typedef struct s_angles
{
	float alpha;
	float beta;
	float gamma;
}	t_angles;

typedef struct s_distances
{
	float	t1;
	float	t2;
}	t_distances;

t_vector	create_vector(const t_vector *start, const t_vector *end);
bool		cylinder_height(t_object *cylinder, float t, t_vector ray, t_vector rot_pixel);
float		dot_product(const t_vector *v1, const t_vector *v2);
void		find_angles(t_angles *angles, t_vector rotation, int direction);
t_distances	find_distances(t_vector ray, t_vector rot_pixel, t_object cylinder);
void		generate_image(t_display *display, t_world *world);
void		initialize_eye(t_vector *eye, t_world world);
void		initialize_pixel(t_vector *pixel, t_world world, int x, int y);
void		intesect_cylinder(t_vector	eye, t_vector pixel, t_object *cylinder);
void		intersect_plane(t_vector pixel, const t_vector *ray, t_object *plane);
void		intersect_sphere(const t_vector *pixel, const t_vector *ray, t_object *sphere);
float		magnitude(t_vector vec);
void		normalize_vector(t_vector *v);
void		print_parsing(t_world world);
t_vector	rotated_cam_ray(t_vector *pixel, t_vector *eye, t_world world);
void		rotation_process(t_vector vec, t_vector center,
			t_vector *rot_vec, t_angles angles);
float		square(float nbr);
void		translation(t_vector *vec, t_vector new_origin);
void		xyz_rotation_matrix(t_vector original, t_vector *rotated, t_angles angles);

#endif