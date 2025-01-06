// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   shadow.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/18 17:40:18 by jayzatov          #+#    #+#             */
// /*   Updated: 2024/12/04 14:03:21 by jayzatov         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #define _GNU_SOURCE
// #include <stdbool.h>
// #include <math.h>
// #include <stdlib.h>
// #include <stdio.h>

// #include "libft.h"
// #include "mlx.h"

// #include "world.h"
// #include "parsing.h"

// typedef struct s_lights
// {
//     int r;
//     int g;
//     int b;
// }   t_lights;

// static t_vector    find_hit_pt(t_vector pixel, t_vector ray, double t_dist)
// {
//     t_vector ray_norm;
//     t_vector pt_on_sphere;

//     ray_norm = ray;
//     normalize_vector(&ray_norm);
//     pt_on_sphere.x = pixel.x + (t_dist * ray_norm.x);
//     pt_on_sphere.y = pixel.y + (t_dist * ray_norm.y);
//     pt_on_sphere.z = pixel.z + (t_dist * ray_norm.z);

//     return (pt_on_sphere);
// }

// static t_vector sphere_norm(t_vector pt_on_sphere, t_object sphere)
// {
//     t_vector sphere_norm;

//     sphere_norm.x = pt_on_sphere.x - sphere.position.x;
//     sphere_norm.y = pt_on_sphere.y - sphere.position.y;
//     sphere_norm.z = pt_on_sphere.z - sphere.position.z;
//     normalize_vector(&sphere_norm); 
    
//     return (sphere_norm);
// }

// // static t_vector cylinder_proj(t_vector V, t_object cylinder)
// // {
// //     t_vector proj;
// //     t_vector axe_norm = cylinder.direction;
// //     normalize_vector(&axe_norm);

// //     proj.x = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.x;
// //     proj.y = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.y;
// //     proj.z = (dot_product(&V, &axe_norm) / dot_product(&axe_norm, &axe_norm)) * cylinder.direction.z;

// //     return (proj);
// // }


// static t_vector cylinder_norm(t_vector pt_on_cyl, t_object cylinder)
// {
//     // t_vector V = create_vector(&cylinder.position, &pt_on_cyl);
//     // normalize_vector(&V);

//     // t_vector proj = cylinder_proj(V, cylinder);
//     // normalize_vector(&proj);

    
//     // t_vector Vperp;
//     // Vperp.x = V.x - proj.x;
//     // Vperp.y = V.y - proj.y;
//     // Vperp.z = V.z - proj.z;

//     // t_vector N = Vperp;
//     /////////////////////////////////////////////////////
//     // normalize_vector(&N);
    
//     // normalize_vector(&light);
//     // double cos = dot_product(&N, &light);
//     // if (cos > 0.0f)
//     // {
//     //     N = scal_x_vec(-1.0f, N);
//         // (void)figure;
//         // (void)light;
//     //     figure->color.r = 255;
//     //     figure->color.g = 255;
//     //     figure->color.b = 255;
//     // }

//     cylinder.position.y = pt_on_cyl.y;
//     t_vector N = create_vector(&cylinder.position, &pt_on_cyl);
//     normalize_vector(&N);
    
//     return (N);
// }

// static void color_limit(int *color)
// {
//     if (*color > 255)
//         *color = 255;
//     // else if (*color < 0)
//     //     *color = 0;
//     return ;
// }



// t_color    shadow_on_figure(double t_dist, t_object figure, t_world world,
//             int in_or_out, t_vector pixel, t_vector ray)
// {
//     printf("shadow on %u\n", figure.type);
//     t_color color;

//     t_vector pt_on_figure = find_hit_pt(pixel, ray, t_dist);


//     t_vector N;
//     t_vector    rot_light = world.light_position;

//     if (figure.type == SPHERE)
//         N = sphere_norm(pt_on_figure, figure);
//     else if (figure.type == CYLINDER)
//     {
//         N = cylinder_norm(pt_on_figure, figure);
        
//         t_angles	angles;

//         find_angles(&angles, figure.direction, -1);
// 	    rotation_process(world.light_position, figure.position, &rot_light, angles);
//     }
//     t_vector L = create_vector(&pt_on_figure, &rot_light); // du point vers la lumiere
//     t_vector V = create_vector(&pt_on_figure, &pixel); // du point vers la camera == pixel ?
//     normalize_vector(&L);
//     normalize_vector(&V);

//     // double cos = dot_product(&N, &L);
//     // if (cos > 0)
//     // {
//         N.x *= in_or_out;
//         N.y *= in_or_out;
//         N.z *= in_or_out;
//     // }


//     double dot_LN = dot_product(&L, &N); // = cos de l'angle L et N
    
//     t_vector R; // rayon réfléchi
//     R.x = 2 * dot_LN * N.x - L.x;
//     R.y = 2 * dot_LN * N.y - L.y;
//     R.z = 2 * dot_LN * N.z - L.z;
//     normalize_vector(&R);
//     (void)R;


//     t_lights specular_l;
//     t_lights diffuse_l;
//     t_lights ambient_l;

//     ambient_l.r = world.ambient_power * world.ambient_color.r;
//     ambient_l.g = world.ambient_power * world.ambient_color.g;
//     ambient_l.b = world.ambient_power * world.ambient_color.b;


//     if (dot_product(&R, &V) > 0 && dot_LN > 0)
//     {
//         specular_l.r = pow(dot_product(&R, &V), 1) * world.light_power * world.light_color.r;
//         specular_l.g = pow(dot_product(&R, &V), 1) * world.light_power * world.light_color.g;
//         specular_l.b = pow(dot_product(&R, &V), 1) * world.light_power * world.light_color.b;
//     }
//     else
//     {
//         specular_l.r = 0;
//         specular_l.g = 0;
//         specular_l.b = 0;
//     }
    
//     // (void)specular_l;
//     (void)ambient_l;
//     // (void)diffuse_l;

//     if (dot_LN < 0)
//         dot_LN = 0;
//     diffuse_l.r = dot_LN * (world.light_power * world.light_color.r);
//     diffuse_l.g = dot_LN * (world.light_power * world.light_color.g);
//     diffuse_l.b = dot_LN * (world.light_power * world.light_color.b);
    

    
   
//     color.r = figure.color.r * ((ambient_l.r /*+ diffuse_l.r + specular_l.r*/) / 255.f);
//     color_limit(&color.r);
//     color.g = figure.color.g * ((ambient_l.g /*+ diffuse_l.g + specular_l.g*/) / 255.f);
//     color_limit(&color.g);
//     color.b = figure.color.b * ((ambient_l.b /*+ diffuse_l.b + specular_l.b*/) / 255.f);
//     color_limit(&color.b);

//     // color.r = dot_LN * (world.light_power * world.light_color.r) * sphere.color.r;
//     // color_limit(&color.r);
//     // color.g = dot_LN * (world.light_power * world.light_color.g) * sphere.color.g;
//     // color_limit(&color.g);
//     // color.b = dot_LN * (world.light_power * world.light_color.b) * sphere.color.b;
//     // color_limit(&color.b);

//     //  if (t_dist == 0)
//     // {
//     //     printf("color.r : %d AND diff.r %d\n", color.r, diffuse_l.r);
//     // }
    
//     return (color);
// }

// /////////////////////////////////////////////////

//     // double dot = dot_product(&light, &sphere_norm);
//     // dot = dot < 0 ? 0 : dot;
//     // color.r =  dot * (sphere.color.r + world.light_power * (double)world.light_color.r);
//     // color.g =  dot * (sphere.color.g + world.light_power * (double)world.light_color.g);
//     // color.b =  dot * (sphere.color.b + world.light_power * (double)world.light_color.b);
//     // color.r += world.ambient_color.r * world.ambient_power;
//     // color.g += world.ambient_color.g * world.ambient_power;
//     // color.b += world.ambient_color.b * world.ambient_power;
//     // color.r = color.r > 255 ? 255 : color.r;
//     // color.g = color.g > 255 ? 255 : color.g;
//     // color.b = color.b > 255 ? 255 : color.b;

    
//     // if (t_dist == 0)
//     // {
//     //     // printf("ray.z %f\n", ray.z);
//     //     printf("r %d\n", color.r);
//     //     printf("g %d\n", color.g);
//     //     printf("b %d\n", color.b);
//     // }


//     // // cos of N and L
//     // t_vector light_cpy = light;
//     // normalize_vector(&light_cpy); 
//     // t_vector norm_cpy = sphere_norm;
//     // normalize_vector(&norm_cpy); 
    
//     // // teta = cos de l'angle entre L et N
//     // double teta = dot_product(&light_cpy, &norm_cpy);
    
//     // if (teta < 0)
//     //     teta = 0;

//     // printf("teta %f\n", teta);
    
//     // // change t_dist to the distance between light and the point

//     // // La lumière diminue en intensité proportionnellement
//     // // au carré de la distance entre le point et la source. La formule classique est :
//     // double attenuation;
//     // t_vector pt_light_dist = create_vector(&light, &pt_on_sphere);
//     // double d = magnitude(pt_light_dist);
//     // if (d == 0) 
//     //     attenuation = 1;
//     // else
//     // {
//     //     // intensité de lumiere de base indépendante de la distance
//     //     double a;
//     //     // attenuation de lumiere modérée
//     //     double b;
//     //     // la plus faible intensité lumineuse
//     //     double c;
//     //     // abc exemples : (scène large) 1.0, 0, 0.01, (scène petite et luimineuse) 1.0,0.1,0.0.
//     //     // précision physique stricte : abc = 1, 0.1, 0.01.
//     //     // forte décroissance avec la distance: abc = 1,0.2,0.01.
//     //     // scène très grande : abc = 1, 0.05, 0.005;
//     //     a = 1.0;
//     //     b = 0.09;
//     //     c = 0.0025;   
//     //     attenuation = 1 / (a + b * d + c * square(d));
//     //     // if ((a + b * d + c * square(d)) > 1)
//     //     //     attenuation = 1;
//     //     attenuation = 1 / (d / 2);
//     // }
//     // // attenuation = 1;
//     // double ambient_intens = /*attenuation * */world.ambient_power;
//     // if (ambient_intens > 1)
//     //     ambient_intens = 1;

    
//     // sphere.color.r = sphere.color.r + (world.ambient_color.r - sphere.color.r) * world.ambient_power;
//     // sphere.color.g = sphere.color.g + (world.ambient_color.g - sphere.color.g) * world.ambient_power;
//     // sphere.color.b = sphere.color.b + (world.ambient_color.b - sphere.color.b) * world.ambient_power;

    
//     // color.r = sphere.color.r * teta
//     //        * ((world.light_power * world.light_color.r) * attenuation);
//     // if (color.r > 255)
//     //    color.r = 255; 
//     // color.g = /*(ambient_intens * world.ambient_color.g) + */sphere.color.g * teta
//     //             * ((world.light_power * world.light_color.r) * attenuation);
//     // if (color.g > 255)
//     //    color.g = 255; 
//     // color.b = /*(ambient_intens * world.ambient_color.b) + */sphere.color.b * teta
//     //             * ((world.light_power * world.light_color.r) * attenuation);
//     // if (color.b > 255)
//     //    color.b = 255; 
    
    
//     //  if (t_dist == 0)
//     // {
//     //     printf("AFTER :\n");
//     //     printf("r %d\n", color.r);
//     //     printf("g %d\n", color.g);
//     //     printf("b %d\n", color.b);
//     // }

// /////////////////////////////////////////////////