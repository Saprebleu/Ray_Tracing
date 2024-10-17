#include <stdlib.h>
#include <stdio.h>

#include "parsing.h"

static char *get_object_type_string(t_object_type object_type)
{
	switch (object_type)
	{
		case PLANE:
			return ("PLANE");

		case SPHERE:
			return ("SPHERE");

		case CYLINDER:
			return ("CYLINDER");

		default:
			abort();
	}
}

void print_parsing(t_world world)
{
	printf("Ambient Color    = %d / %d / %d\n", world.ambient_color.r, world.ambient_color.g, world.ambient_color.b);
	printf("Ambient Power    = %f\n", world.ambient_power);
	printf("\n");
	printf("Camera Position  = %f / %f / %f\n", world.camera_position.x, world.camera_position.y, world.camera_position.z);
	printf("Camera Direction = %f / %f / %f\n", world.camera_direction.x, world.camera_direction.y, world.camera_direction.z);
	printf("Camera FOV       = %d\n", world.camera_fov);
	printf("\n");
	printf("Light Position   = %f / %f / %f\n", world.light_position.x, world.light_position.y, world.light_position.z);
	printf("Light Color      = %d / %d / %d\n", world.light_color.r, world.light_color.g, world.light_color.b);
	printf("Light Power      = %f\n", world.light_power);
	if (world.nb_objects > 0)
	{
		printf("\n");
		printf("OBJECTS:\n");
		printf("\n");
		for (int i = 0; i < world.nb_objects; i++)
		{
			printf("[%d] Object Type = %s\n", i, get_object_type_string(world.objects[i].type));
			switch (world.objects[i].type)
			{
				case SPHERE:
					printf("\tPosition  = %f / %f / %f\n", world.objects[i].position.x, world.objects[i].position.y, world.objects[i].position.z);
					printf("\tColor     = %d / %d / %d\n", world.objects[i].color.r, world.objects[i].color.g, world.objects[i].color.b);
					printf("\tRadius    = %f\n", world.objects[i].radius);
					break ;

				case CYLINDER:
					printf("\tPosition  = %f / %f / %f\n", world.objects[i].position.x, world.objects[i].position.y, world.objects[i].position.z);
					printf("\tDirection = %f / %f / %f\n", world.objects[i].direction.x, world.objects[i].direction.y, world.objects[i].direction.z);
					printf("\tColor     = %d / %d / %d\n", world.objects[i].color.r, world.objects[i].color.g, world.objects[i].color.b);
					printf("\tRadius    = %f\n", world.objects[i].radius);
					printf("\tHeight    = %f\n", world.objects[i].height);
					break ;

				case PLANE:
					printf("\tPosition  = %f / %f / %f\n", world.objects[i].position.x, world.objects[i].position.y, world.objects[i].position.z);
					printf("\tDirection = %f / %f / %f\n", world.objects[i].direction.x, world.objects[i].direction.y, world.objects[i].direction.z);
					printf("\tColor     = %d / %d / %d\n", world.objects[i].color.r, world.objects[i].color.g, world.objects[i].color.b);
					break ;

				default:
					abort();
			}
		}
	}
}