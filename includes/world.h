#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

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
    bool        has_ambient;
	t_color     ambient_color;
	float       ambient_power;

    bool        has_camera;
	t_vector    camera_position;
	t_vector    camera_direction;
	int         camera_fov;

    bool        has_light;
	t_vector    light_position;
	t_color     light_color;
	float       light_power;

	int         nb_objects;
	t_object    *objects;
} t_world;

#endif