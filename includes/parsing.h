#ifndef PARSING_H
#define PARDING_H

#include <stdbool.h>

typedef struct s_parsed
{
	bool has_ambient;
	bool has_camera;
	bool has_light;
} t_parsed;

typedef enum e_object_type
{
	NONE = 0,
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3
} t_object_type;

typedef struct s_vector
{
	float x;
	float y;
	float z;
} t_vector;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_object
{
	t_object_type   type;

	t_vector        position;
	t_vector        direction;
	float           radius;
	float           height;
	t_color         color;
} t_object;

typedef struct s_world
{
	t_color     ambient_color;
	float       ambient_power;

	t_vector    camera_position;
	t_vector    camera_direction;
	int         camera_fov;

	t_vector    light_position;
	t_color     light_color;
	float       light_power;

	t_object    *objects;
	int         nb_objects;
} t_world;


#endif