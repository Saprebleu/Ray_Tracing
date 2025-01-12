/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:48:55 by tjarross          #+#    #+#             */
/*   Updated: 2025/01/12 19:01:23 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

// instead of defining "_GNU_SOURCE",
// to allow portability :
// (works with math.h for math macros)

#define _XOPEN_SOURCE 700
#include <math.h>

# define WINDOW_TITLE	"miniRT"
# define WINDOW_WIDTH	1024
# define WINDOW_HEIGHT	768
# define SHINE			130
# include <stdbool.h>

typedef enum e_object_type
{
	NONE = 0,
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3
}	t_object_type;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
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
	t_vector		normal;
	double			diameter;
	double			height;
	t_color			color;
	t_color			pt_color;
	double			t_min;
	int				index;
}	t_object;

typedef struct s_world
{
	bool		has_ambient;
	t_color		ambient_color;
	double		ambient_power;
	bool		has_camera;
	t_vector	camera_position;
	t_vector	camera_direction;
	int			camera_fov;
	bool		has_light;
	t_vector	light_position;
	t_color		light_color;
	double		light_power;
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
	double alpha;
	double beta;
	double gamma;
}	t_angles;

typedef struct s_distances
{
	double	t1;
	double	t2;
}	t_distances;

typedef struct s_fig_info
{
	t_vector	pt_on_figure;
	t_vector	normal;
	int			in_or_out;
	t_world		wrld;
}	t_fig_info;

typedef struct s_mirror
{
	t_vector	strt;
	t_vector	rot_strt;
	t_vector	dir;
	t_vector	rot_dir;
	t_vector	ray;
	t_vector	rot_ray;
}	t_mirror;

typedef struct s_light
{
    int r;
    int g;
    int b;
} t_light;

typedef struct s_lights
{
    t_light specular;
    t_light diffuse;
    t_light ambient;
    t_vector lig_ray;
    double  lig_mag;
}   t_lights;

t_vector	create_vector(const t_vector *start, const t_vector *end);
bool		cylinder_height(t_object *cylinder, double t, t_vector ray, t_vector rot_pixel);
double		dot_product(const t_vector *v1, const t_vector *v2);
void		find_angles(t_angles *angles, t_vector rotation, int direction);

// void		find_distances(t_vector ray, t_vector rot_pixel, t_object figure,
// 			t_distances	*dist);
		
void		generate_image(t_display *display, t_world *world);
void		initialize_eye(t_vector *eye, t_world world);
void		initialize_pixel(t_vector *pixel, t_world world, int x, int y);
void		intesect_cylinder(t_vector pixel, t_vector eye, t_object *cylinder, t_world world);
void		intersect_plane(t_vector pixel, t_vector ray, t_object *plane, t_world world);
void		intersect_sphere(t_vector pixel, t_vector ray, t_object *sphere, t_world world);

void		init_mirror(t_mirror *a, t_vector *eye, t_vector pixel, t_vector *ray);
t_vector	cyl_distances(t_vector *start, t_vector *dir, const t_object *cylinder,
			t_distances *dist);
t_vector	rotated(t_vector *eye, t_vector *pixel, t_object cylinder);

void		t_for_plane(t_vector origin, t_vector ray,
			const t_object *plane, t_distances *dist);
void		t_for_sphere(t_vector origin, t_vector ray, const t_object *sphere,
			t_distances *dist);
void		t_for_cylinder(t_vector rot_pixel, t_vector rot_ray, t_object cylinder,
			t_distances *dist);

			
void		plane_norm(t_fig_info *fig_inf, t_object plane);
void		sphere_norm(t_fig_info *fig_inf, t_object sphere);
void		cylinder_norm(t_fig_info *fig_inf, t_vector pt_on_cyl, t_object cylinder);

void	put_light(t_object *figure, float t, t_fig_info fig_inf, t_mirror a);
t_color	light_n_shade(t_fig_info fig_inf, t_vector pixel, t_object figure, t_world world);

// SHADOW

// t_color		shadow_on_figure(double t_dist, t_object figure, t_world world,
// 			int in_or_out, t_vector pixel, t_vector ray);



double		magnitude(t_vector vec);
void		normalize_vector(t_vector *v);
void		print_parsing(t_world world);
t_vector	rotated_cam_ray(t_vector *pixel, t_vector *eye, t_world world);
t_vector		rotation_process(t_vector vec, t_vector center,
			t_vector *rot_vec, t_angles angles);
void	solve_polynom(double a, double b, double c, t_distances *dst);

// void	solve_polynom(double a, double b, double c, t_distances *dst);

double		square(double nbr);
void		translation(t_vector *vec, t_vector new_origin);
void		xyz_rotation_matrix(t_vector original, t_vector *rotated, t_angles angles);

// void	solve_poly(double a, double b, double c, t_distances *dst);
// t_distances	two_ts(double a, double b, double c);

t_vector    find_hit_pt(t_vector origin, t_vector ray, double t_dist);

#endif