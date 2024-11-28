/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:40:18 by jayzatov          #+#    #+#             */
/*   Updated: 2024/11/28 16:48:45 by jayzatov         ###   ########.fr       */
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

typedef struct s_lights
{
    int r;
    int g;
    int b;
}   t_lights;

static t_vector    find_hit_pt(t_vector pixel, t_vector ray, float t_dist)
{
    t_vector ray_norm;
    t_vector pt_on_sphere;

    ray_norm = ray;
    normalize_vector(&ray_norm);
    pt_on_sphere.x = pixel.x + (t_dist * ray_norm.x);
    pt_on_sphere.y = pixel.y + (t_dist * ray_norm.y);
    pt_on_sphere.z = pixel.z + (t_dist * ray_norm.z);

    return (pt_on_sphere);
}

static t_vector sphere_norm(t_vector pt_on_sphere, t_object sphere)
{
    t_vector sphere_norm;

    sphere_norm.x = pt_on_sphere.x - sphere.position.x;
    sphere_norm.y = pt_on_sphere.y - sphere.position.y;
    sphere_norm.z = pt_on_sphere.z - sphere.position.z;
    normalize_vector(&sphere_norm); 
    
    return (sphere_norm);
}

// static t_vector cylinder_proj(t_vector V, t_object cylinder)
// {
//     t_vector proj;
//     t_vector axe_norm = cylinder.direction;
//     normalize_vector(&axe_norm);

//     proj.x = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.x;
//     proj.y = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.y;
//     proj.z = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.z;

//     return (proj);
// }

t_vector		scal_x_vec(float n, t_vector p)
{
	t_vector	v;

	v.x = n * p.x;
	v.y = n * p.y;
	v.z = n * p.z;
	return (v);
}

static t_vector cylinder_norm(t_vector pt_on_cyl, t_object cylinder)
{
    // t_vector V = create_vector(&cylinder.position, &pt_on_cyl);
    // normalize_vector(&V);

    // t_vector proj = cylinder_proj(V, cylinder);
    // normalize_vector(&proj);

    
    // t_vector Vperp;
    // Vperp.x = V.x - proj.x;
    // Vperp.y = V.y - proj.y;
    // Vperp.z = V.z - proj.z;

    // t_vector N = Vperp;
    /////////////////////////////////////////////////////
    // normalize_vector(&N);
    
    // normalize_vector(&light);
    // float cos = dot_product(&N, &light);
    // if (cos > 0.0f)
    // {
    //     N = scal_x_vec(-1.0f, N);
        // (void)figure;
        // (void)light;
    //     figure->color.r = 255;
    //     figure->color.g = 255;
    //     figure->color.b = 255;
    // }

    cylinder.position.y = pt_on_cyl.y;
    t_vector N = create_vector(&cylinder.position, &pt_on_cyl);
    normalize_vector(&N);
    
    return (N);
}

void color_limit(int *color)
{
    if (*color > 255)
        *color = 255;
    // else if (*color < 0)
    //     *color = 0;
    return ;
}



t_color    light_on_figure(t_vector pixel, t_vector ray, float t_dist, t_object figure, t_world world,
            int in_or_out)
{
    printf("light on %u\ncolor.r = %d\n", figure.type, figure.color.b);

    t_color color;

    t_vector pt_on_figure = find_hit_pt(pixel, ray, t_dist);


    t_vector N;
    t_vector    rot_light = world.light_position;
    t_angles	angles;

    if (figure.type == SPHERE)
        N = sphere_norm(pt_on_figure, figure);
    else if (figure.type == CYLINDER)
    {
        N = cylinder_norm(pt_on_figure, figure);
        
        find_angles(&angles, figure.direction, -1);
	    rotation_process(world.light_position, figure.position, &rot_light, angles);
    }
    // t_vector L_no_rot = create_vector(&pt_on_figure, &world.light_position);
    // normalize_vector(&L_no_rot);
    t_vector L = create_vector(&pt_on_figure, &rot_light); // du point vers la lumiere
    t_vector V = create_vector(&pt_on_figure, &pixel); // du point vers la camera == pixel ?
    normalize_vector(&L);
    normalize_vector(&V);


    t_vector N_cpy = N;
    // permet d'avoir la lumiere dans les t2 (interieur du cylindre)
    // en multipliant par -1;
    // float cos = dot_product(&N, &L);
    // if (cos < 0 && in_or_out == -1)
    // {
    // // // if (in_or_out == MAXFLOAT)
    // // // {
        N.x *= in_or_out;
        N.y *= in_or_out;
        N.z *= in_or_out;
    // }
    (void)in_or_out;


    float dot_LN = dot_product(&L, &N); // = cos de l'angle L et N
    
    t_vector R; // rayon réfléchi
    R.x = 2 * dot_LN * N.x - L.x;
    R.y = 2 * dot_LN * N.y - L.y;
    R.z = 2 * dot_LN * N.z - L.z;
    normalize_vector(&R);
    (void)R;


    t_lights specular_l;
    t_lights diffuse_l;
    t_lights ambient_l;

    ambient_l.r = world.ambient_power * world.ambient_color.r;
    ambient_l.g = world.ambient_power * world.ambient_color.g;
    ambient_l.b = world.ambient_power * world.ambient_color.b;


    if (dot_product(&R, &V) > 0 && dot_LN > 0)
    {
        specular_l.r = powf(dot_product(&R, &V), 1) * world.light_power * world.light_color.r;
        specular_l.g = powf(dot_product(&R, &V), 1) * world.light_power * world.light_color.g;
        specular_l.b = powf(dot_product(&R, &V), 1) * world.light_power * world.light_color.b;
    }
    else
    {
        specular_l.r = 0;
        specular_l.g = 0;
        specular_l.b = 0;
    }
    
    // (void)specular_l;
    // (void)ambient_l;
    // (void)diffuse_l;

    if (dot_LN < 0)
        dot_LN = 0;
        
    diffuse_l.r = dot_LN * (world.light_power * world.light_color.r);
    diffuse_l.g = dot_LN * (world.light_power * world.light_color.g);
    diffuse_l.b = dot_LN * (world.light_power * world.light_color.b);
    
    (void)in_or_out;
    

    int j = -1;
    t_distances dist;
    
	while (++j < world.nb_objects)
	{
		/*if (world.objects[j].type == SPHERE)
		else */if (world.objects[j].type == CYLINDER)
        {
            // pt_on_figure = 
            t_object neighbour;
            neighbour = world.objects[j];
            
            // n'a pas l'air de changer le cylindre lui-même?
            rotation_process(world.objects[j].position, figure.position, &neighbour.position, angles);

            // if (figure.color.r == 255)
            //     printf("!?! on est sur le rouge %f, %f, %f\n",
            //     pt_on_figure.x, pt_on_figure.y, pt_on_figure.z);
            // else if (figure.color.b == 255)
            //     printf("!?! on est sur le bleu %f, %f, %f\n",
            //     pt_on_figure.x, pt_on_figure.y, pt_on_figure.z);
                
              
            dist.t1 = MAXFLOAT;
            dist.t2 = MAXFLOAT;
            dist = find_distances(L, pt_on_figure, neighbour);
            // if (dist.t1 == 0)
                // dist = find_distances(L, pt_on_figure, world.objects[j]);
            float min = fminf(dist.t1, dist.t2);
		    float max = fmaxf(dist.t1, dist.t2);
		    dist.t1 = min;
		    dist.t2 = max;

            // if (((/*dist.t1 != MAXFLOAT && */dist.t1 > 0.0001 && cylinder_height(&world.objects[j], dist.t1, L,  pt_on_figure))
                /*&& (in_or_out == 1)*/
                // || ((/*dist.t2 != MAXFLOAT && */dist.t2 > 0.001 && cylinder_height(&world.objects[j], dist.t1, L,  pt_on_figure))
                // /*&& in_or_out == 1*/)
                if (
                    (in_or_out == -1 && dist.t2 != MAXFLOAT && dist.t2 >= 0.0001 && cylinder_height(&neighbour, dist.t2, L,  pt_on_figure) )
                    || (in_or_out == -1 && dist.t1 != MAXFLOAT && dist.t1 >= 0.0001 && cylinder_height(&neighbour, dist.t1, L,  pt_on_figure) )
                    
                    || (in_or_out == 1 && dist.t2 != MAXFLOAT && dist.t2 >= 0.0001 && cylinder_height(&neighbour, dist.t2, L,  pt_on_figure))
                    || (in_or_out == 1 && dist.t1 != MAXFLOAT && dist.t1 >= 0.1 && cylinder_height(&neighbour, dist.t1, L,  pt_on_figure))
                )
            {
                
                if (neighbour.color.r == 255 && figure.color.b == 255
                        && in_or_out == 1)
                {
                    t_vector blue_pt = find_hit_pt(pt_on_figure, L, dist.t1);
                    printf("Intersection trouvée sur le bleu %f, %f, %f\n", blue_pt.x, blue_pt.y, blue_pt.z);
                    // printf("A la distance %f\n", dist.t1);
                    printf("Lnorm : %f, %f, %f\n", L.x, L.y, L.z);
                }
                else if (neighbour.color.b == 255 && figure.color.r == 255
                        && in_or_out == 1)
                    printf("Intersection trouvée sur le rouge\n");
                // else
                // {
                //     printf("Pas d'intersection j = %d\n", j);
                //     // break;
                // }
                // printf("SHADOW\n");
                diffuse_l.r = 0;
                diffuse_l.g = 0;
                diffuse_l.b = 0;
                specular_l.r = 0;
                specular_l.g = 0;
                specular_l.b = 0;
                // if (in_or_out == 1)
                // {
                //     ambient_l.r = 0;
                //     ambient_l.g = 0;
                //     ambient_l.b = 0;
                // }
                    
                break ;
            }
        }
		// else if (world.objects[j].type == PLANE)
			// intersect_plane(pixel, &ray, &world.objects[j]);
	}

//     // TEST
//     // float cos = dot_product(&N, &L);
//     // // float cos_cpy = dot_product(&N_cpy, &L);
//     // if ((cos < 0 && in_or_out == -1)
//     //     /*|| (cos_cpy < 0 && in_or_out == -1)*/)
//     // {
//     //      diffuse_l.r = 0;
//     //     diffuse_l.g = 0;
//     //     diffuse_l.b = 0;
//     //     specular_l.r = 0;
//     //     specular_l.g = 0;
//     //     specular_l.b = 0;
//     //     ambient_l.r = 0;
//     //     ambient_l.g = 0;
//     //     ambient_l.b = 0;
//     // }
    (void)N_cpy;
    
    color.r = figure.color.r * ((ambient_l.r + diffuse_l.r + specular_l.r) / 255.f);
    color_limit(&color.r);
    color.g = figure.color.g * ((ambient_l.g + diffuse_l.g + specular_l.g) / 255.f);
    color_limit(&color.g);
    color.b = figure.color.b * ((ambient_l.b + diffuse_l.b + specular_l.b) / 255.f);
    color_limit(&color.b);

 
//     printf("color.r = %d\n", color.b);

    return (color);
}

/////////////////////////////////////////////////

    // float dot = dot_product(&light, &sphere_norm);
    // dot = dot < 0 ? 0 : dot;
    // color.r =  dot * (sphere.color.r + world.light_power * (float)world.light_color.r);
    // color.g =  dot * (sphere.color.g + world.light_power * (float)world.light_color.g);
    // color.b =  dot * (sphere.color.b + world.light_power * (float)world.light_color.b);
    // color.r += world.ambient_color.r * world.ambient_power;
    // color.g += world.ambient_color.g * world.ambient_power;
    // color.b += world.ambient_color.b * world.ambient_power;
    // color.r = color.r > 255 ? 255 : color.r;
    // color.g = color.g > 255 ? 255 : color.g;
    // color.b = color.b > 255 ? 255 : color.b;

    
    // if (t_dist == 0)
    // {
    //     // printf("ray.z %f\n", ray.z);
    //     printf("r %d\n", color.r);
    //     printf("g %d\n", color.g);
    //     printf("b %d\n", color.b);
    // }


    // // cos of N and L
    // t_vector light_cpy = light;
    // normalize_vector(&light_cpy); 
    // t_vector norm_cpy = sphere_norm;
    // normalize_vector(&norm_cpy); 
    
    // // teta = cos de l'angle entre L et N
    // float teta = dot_product(&light_cpy, &norm_cpy);
    
    // if (teta < 0)
    //     teta = 0;

    // printf("teta %f\n", teta);
    
    // // change t_dist to the distance between light and the point

    // // La lumière diminue en intensité proportionnellement
    // // au carré de la distance entre le point et la source. La formule classique est :
    // float attenuation;
    // t_vector pt_light_dist = create_vector(&light, &pt_on_sphere);
    // float d = magnitude(pt_light_dist);
    // if (d == 0) 
    //     attenuation = 1;
    // else
    // {
    //     // intensité de lumiere de base indépendante de la distance
    //     float a;
    //     // attenuation de lumiere modérée
    //     float b;
    //     // la plus faible intensité lumineuse
    //     float c;
    //     // abc exemples : (scène large) 1.0, 0, 0.01, (scène petite et luimineuse) 1.0,0.1,0.0.
    //     // précision physique stricte : abc = 1, 0.1, 0.01.
    //     // forte décroissance avec la distance: abc = 1,0.2,0.01.
    //     // scène très grande : abc = 1, 0.05, 0.005;
    //     a = 1.0;
    //     b = 0.09;
    //     c = 0.0025;   
    //     attenuation = 1 / (a + b * d + c * square(d));
    //     // if ((a + b * d + c * square(d)) > 1)
    //     //     attenuation = 1;
    //     attenuation = 1 / (d / 2);
    // }
    // // attenuation = 1;
    // float ambient_intens = /*attenuation * */world.ambient_power;
    // if (ambient_intens > 1)
    //     ambient_intens = 1;

    
    // sphere.color.r = sphere.color.r + (world.ambient_color.r - sphere.color.r) * world.ambient_power;
    // sphere.color.g = sphere.color.g + (world.ambient_color.g - sphere.color.g) * world.ambient_power;
    // sphere.color.b = sphere.color.b + (world.ambient_color.b - sphere.color.b) * world.ambient_power;

    
    // color.r = sphere.color.r * teta
    //        * ((world.light_power * world.light_color.r) * attenuation);
    // if (color.r > 255)
    //    color.r = 255; 
    // color.g = /*(ambient_intens * world.ambient_color.g) + */sphere.color.g * teta
    //             * ((world.light_power * world.light_color.r) * attenuation);
    // if (color.g > 255)
    //    color.g = 255; 
    // color.b = /*(ambient_intens * world.ambient_color.b) + */sphere.color.b * teta
    //             * ((world.light_power * world.light_color.r) * attenuation);
    // if (color.b > 255)
    //    color.b = 255; 
    
    
    //  if (t_dist == 0)
    // {
    //     printf("AFTER :\n");
    //     printf("r %d\n", color.r);
    //     printf("g %d\n", color.g);
    //     printf("b %d\n", color.b);
    // }

/////////////////////////////////////////////////