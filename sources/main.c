/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjarross <tjarross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:29:08 by tjarross          #+#    #+#             */
/*   Updated: 2024/11/03 23:19:55 by tjarross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "mlx.h"

#include "world.h"
#include "parsing.h"

void	print_parsing(t_world world);

void	set_pixel_color(t_display *display, int x, int y, const t_color *color)
{
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 0] = color->b;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 1] = color->g;
	display->image_buffer[y * display->size_line
		+ x * display->bits_per_pixel / 8 + 2] = color->r;
}

// Gives a number resulting of the multiplication of 2 vectors.
// The dot product can be useful to :
// 		- calcualte the distance.
//		- determine angles.
//		- determine whether an object is aiming towards another
//		  or the contrary.

float	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	create_vector(const t_vector *start, const t_vector *end)
{
	t_vector	v;

	v.x = end->x - start->x;
	v.y = end->y - start->y;
	v.z = end->z - start->z;
	return (v);
}

float	solve_polynom(float a, float b, float c)
{
	float	delta;
	float	t1;
	float	t2;

	delta = b * b - 4 * a * c;
	if (delta == 0.0f)
		return (-b / (2.0f * a));
	else if (delta > 0.0f)
	{
		t1 = (-b - sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		t2 = (-b + sqrtf(b * b - 4.0f * a * c)) / (2.0f * a);
		if (t1 < 0.0f && t2 < 0.0f)
			return (MAXFLOAT);
		if (t1 < 0.0f)
			return (t2);
		else if (t2 < 0.0f)
			return (t1);
		else
			return (fminf(t1, t2));
	}
	return (MAXFLOAT);
}

// "distance" distance between camera point and the center of a sphere

bool	intersect_sphere(const t_vector *pixel,
	const t_vector *ray, t_object *sphere)
{
	t_vector	distance;
	float		a;
	float		b;
	float		c;

	distance = create_vector(&sphere->position, pixel);
	a = dot_product(ray, ray);
	b = 2.0f * dot_product(ray, &distance);
	c = dot_product(&distance, &distance)
		- ((sphere->diameter / 2.0f) * (sphere->diameter / 2.0f));
	sphere->t_min = solve_polynom(a, b, c);
	return (sphere->t_min != MAXFLOAT);
}

float square(float x) {
    return x * x;
}
void normalize_vector(t_vector *v)
{
	float	length = sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));

	v->x /= length;
	v->y /= length;
	v->z /= length;
}

bool	intesect_cylinder(const t_vector *pixel, const t_vector *ray, t_object *cylinder,
		int x, int y)
{
	// float x = cylinder->position.x;
	// float y = cylinder->position.y;
	float		a;
	float		b;
	float		c;
	// a = (pixel.x * pixel.x + pixel.y * pixel.y);
	// b = (2.0f*(0.0f)*pixel.x + 2.0f*(0.0f)*pixel.y);
	
	t_vector distance = create_vector(&cylinder->position, pixel);

	// ray au carré
	a = (ray->x * ray->x + ray->z * ray->z);
	// 2 fois chaque coordonnée de ray * chaque coordonnée de distance
	b = 2.0f * (ray->x * distance.x) + 2.0f * (ray->z * distance.z);
	c = (distance.x * distance.x + distance.z * distance.z)
		- ((cylinder->diameter / 2.0f) * (cylinder->diameter / 2.0f));
	
	cylinder->t_min = solve_polynom(a, b, c);
	
	if (cylinder->t_min != MAXFLOAT)
	{	
		// float	normalized_ray = sqrtf(powf(ray->x, 2) + powf(ray->y, 2) + powf(ray->z, 2));
		// t_vector	ray_norm;
		// ray_norm.x = ray->x/normalized_ray;
		// ray_norm.y = ray->y/normalized_ray;
		// ray_norm.z = ray->z/normalized_ray;
		
		t_vector	figure_point;
		// X camera position MAIS la position de l'oeil
		// -> il n'y a que le z qui change par rapport aux coordonnees de la camera
		// Il faut normaliser ray
		
		figure_point.x = pixel->x + (cylinder->t_min * ray->x);
		figure_point.y = pixel->y + (cylinder->t_min * ray->y);
		figure_point.z = pixel->z + (cylinder->t_min * ray->z);
		if (x == 1024/2 && y == 768/2)
		{
			printf("\nray_norm x: %f, y: %f, z: %f\n", ray->x, ray->y, ray->z);
			printf("cylinder->t_min %f\n", cylinder->t_min);
			printf("POINT (%f, %f, %f)\n", figure_point.x, figure_point.y, figure_point.z);
			printf("EYE x: %f, y: %f, z: %f\n", pixel->x, pixel->y, pixel->z);
		}
		
		float	point_center_dist = (square((figure_point.x - cylinder->position.x)) +
									 square((figure_point.y - cylinder->position.y))+
									 square((figure_point.z - cylinder->position.z)));
											
		if (x == 1024/2 && y == 768/2)
			printf("\npoint_center_dist %f, sqrt %f\n", point_center_dist, sqrtf(point_center_dist));
		// point_center_dist = sqrtf(point_center_dist);


		float		pythagore_solution;
		pythagore_solution = point_center_dist - square((cylinder->diameter / 2.0f));
		
		if (x == 1024/2 && y == 768/2)
		{
			printf("cylinder->rayon %f, squre %f\n", (cylinder->diameter / 2.0f), square((cylinder->diameter / 2.0f)));
			printf("pythagore_solution %f\n", sqrtf(pythagore_solution));
		}
		

		pythagore_solution = sqrtf(pythagore_solution);	

		if (x == 1024/2 && y == 768/2)
		{
			printf("\n\n(A-C)^2 : %f\n", point_center_dist);
			printf("ray^2 : %f\n", square(cylinder->diameter / 2.0f));
			// printf("DIAMETER : %f\n\n", (cylinder->diameter / 2.0f));
			printf("(A-C)^2 - ray^2 : RESULT^2 = %f\n", point_center_dist - square(cylinder->diameter / 2.0f));
			printf("RESULT : %f\n", sqrtf(point_center_dist - square(cylinder->diameter / 2.0f)));
			printf("H/2 : %f\n\n", (cylinder->height / 2.0f));

			
			// pythagore_solution = sqrtf(fabsf(pythagore_solution));
			printf("SOLUTION : %f\n", fabsf(pythagore_solution));
			printf("cylinder->height %f\n", cylinder->height);
		}
		


		// if (fabsf(pythagore_solution) > (cylinder->height / 2.0f))
		// if (fabsf(pythagore_solution) > cylinder->height)
		// if (fabsf(pythagore_solution) > (cylinder->height / 2.0f))
		if (fabsf(pythagore_solution) > (cylinder->height / 2.0f))
		{
			// printf("pythagore_solution2 %f\n", pythagore_solution);
			cylinder->color.r = 255; 
			cylinder->color.g = 255; 
			cylinder->color.b = 0;
			//JAUNE
			if (x == 1024/2 && y == 768/2)
				printf("JAUNE\n");

			// return (0);	
		}
		else if (fabsf(pythagore_solution) == (cylinder->height / 2.0f))
		{
			cylinder->color.r = 0; 
			cylinder->color.g = 255; 
			cylinder->color.b = 0;
			//ROUGE
			if (x == 1024/2 && y == 768/2)
				printf("ROUGE\n");
		}
		else if (fabsf(pythagore_solution) < (cylinder->height / 2.0f))
		{
			cylinder->color.r = 0; 
			cylinder->color.g = 0; 
			cylinder->color.b = 255;
			if (x == 1024/2 && y == 768/2)
				printf("BLEU\n");

			//BLEU 
		}
		else if (x == 1024/2 && y == 768/2)
		{
			printf("OK -- %f, %f\n", fabsf(pythagore_solution), pythagore_solution);
			
		}	
			
		return (cylinder->t_min != MAXFLOAT);

	}
	
	return (false);
}

// "Camera distance" is calculated thanks to the TOA formula of a right triangle,
// 	knowing fov degrees (converted to radians for tanf()) and screen width.
//  It is the eye-camera distance;

// The "ray" starts at the camera point, goes through each pixel of the screen and
// might encounter a figure.

void	generate_image(t_display *display, t_world *world)
{
	t_vector	ray;
	t_vector	pixel;
	t_vector	eye;
	int			x;
	int			y;
	float		camera_distance;

	camera_distance = ((WINDOW_WIDTH / 2.0f)
						/ tanf((world->camera_fov / 2.0f) * M_PI / 180.0f));
	pixel.z = world->camera_position.z;
	eye.x = world->camera_position.x;
	eye.y = world->camera_position.y;
	eye.z = world->camera_position.z - camera_distance;
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
		{
			pixel.x = world->camera_position.x + (WINDOW_WIDTH / 2.0f) - x;
			pixel.y = world->camera_position.y - (WINDOW_HEIGHT / 2.0f) + y;
			ray = create_vector(&eye, &pixel);
			normalize_vector(&ray);

			
			// intersect_sphere(&world->eye, &ray, &world->objects[0]);
			// intersect_sphere(&world->eye, &ray, &world->objects[1]);
				
			
			// int i = 0;
			// int index_obj = -1;
			// float smallest_tmin = MAXFLOAT;
			// while(i < world->nb_objects)
			// {
			// 	if (world->objects[i].t_min < smallest_tmin)
			// 	{
			// 		index_obj = i;
			// 		smallest_tmin = world->objects[i].t_min;
			// 	}
			// 	i++;
			// }
			// if (index_obj != -1)
			// 	set_pixel_color(display, x, y, &world->objects[index_obj].color);

			if (intesect_cylinder(&pixel, &ray, &world->objects[0], x, y))
				set_pixel_color(display, x, y, &world->objects[0].color);
		}
	}
}

bool	initialize_mlx_context(t_display *display, int window_width,
	int window_height, char *window_title)
{
	
	ft_memset(display, 0, sizeof(*display));
	display->mlx_ptr = mlx_init();
	if (display->mlx_ptr == NULL)
		return (printf("Error\nCannot create mlx context\n"), false);
	display->mlx_window = mlx_new_window(display->mlx_ptr, window_width,
			window_height, window_title);
	if (display->mlx_window == NULL)
		return (printf("Error\nCannot create mlx window\n"), false);
	display->mlx_image = mlx_new_image(display->mlx_ptr, window_width,
			window_height);
	if (display->mlx_image == NULL)
		return (printf("Error\nCannot create mlx image\n"), false);
	display->image_buffer = mlx_get_data_addr(display->mlx_image,
			&display->bits_per_pixel, &display->size_line, &display->endian);
	if (display->image_buffer == NULL)
		return (printf("Error\nCannot get mlx image buffer\n"), false);
	return (true);
}

void	clean_mlx_context(t_display *display)
{
	if (display->mlx_image != NULL)
	{
		mlx_destroy_image(display->mlx_ptr, display->mlx_image);
		display->mlx_image = NULL;
	}
	if (display->mlx_window != NULL)
	{
		mlx_destroy_window(display->mlx_ptr, display->mlx_window);
		display->mlx_window = NULL;
	}
	if (display->mlx_ptr != NULL)
	{
		mlx_destroy_display(display->mlx_ptr);
		free(display->mlx_ptr);
		display->mlx_ptr = NULL;
	}
}

int	main(int argc, char **argv)
{
	t_display	display;
	t_world		world;
	int			parsing_ret;

	if (argc != 2)
		return (printf("Error\nProgram take only one argument\n"),
			EXIT_FAILURE);
	parsing_ret = parse_rt(argv[1], &world);
	if (parsing_ret != 0)
		return (EXIT_FAILURE);
	print_parsing(world);
	if (false == initialize_mlx_context(&display, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE))
		return (clean_mlx_context(&display), EXIT_FAILURE);
	generate_image(&display, &world);
	mlx_put_image_to_window(display.mlx_ptr, display.mlx_window,
		display.mlx_image, 0, 0);
	mlx_loop(display.mlx_ptr);
	clean_mlx_context(&display);
	free(world.objects);
	return (EXIT_SUCCESS);
}
