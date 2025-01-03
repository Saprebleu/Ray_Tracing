/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:40:18 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/03 14:48:39 by jayzatov         ###   ########.fr       */
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
} t_lights;

static t_vector find_hit_pt(t_vector origin, t_vector ray, float t_dist)
{
    t_vector ray_norm;
    t_vector pt_on_sphere;

    ray_norm = ray;
    normalize_vector(&ray_norm);
    pt_on_sphere.x = origin.x + (t_dist * ray_norm.x);
    pt_on_sphere.y = origin.y + (t_dist * ray_norm.y);
    pt_on_sphere.z = origin.z + (t_dist * ray_norm.z);

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

t_vector scal_x_vec(float n, t_vector p)
{
    t_vector v;

    v.x = n * p.x;
    v.y = n * p.y;
    v.z = n * p.z;
    return (v);
}

void zyx_rotation_matrix(t_vector original, t_vector *rotated, t_angles angles)
{
    float alpha;
    float beta;
    float gamma;

    alpha = angles.alpha;
    beta = angles.beta;
    gamma = angles.gamma;
    // rotated->x = ((cosf(beta) * cosf(gamma)) * original.x)
    // + ((sin(alpha) * sin(beta) * cos(gamma) - cos(alpha) * sin(gamma)) * original.y)
    // + ((cos(alpha) * sin(beta) * cos(gamma) + sin(alpha) * sin(gamma)) * original.z);
    rotated->x = ((cosf(alpha) * cosf(beta)) * original.x) + ((cosf(alpha) * sinf(beta) * sinf(gamma) - sinf(alpha) * cosf(gamma)) * original.y) + ((cosf(alpha) * sinf(beta) * cosf(gamma) + sinf(alpha) * sinf(gamma)) * original.z);

    rotated->y = ((sinf(alpha) * cosf(beta)) * original.x) + ((sinf(alpha) * sinf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma)) * original.y) + ((sinf(alpha) * sinf(beta) * cosf(gamma) - cosf(alpha) * sinf(gamma)) * original.z);

    rotated->z = ((-sinf(beta)) * original.x) + ((cosf(beta) * sinf(gamma)) * original.y) + ((cosf(beta) * cosf(gamma)) * original.z);
}

void xyz_rotation_matrix_inverse(t_vector rotated, t_vector *original, t_angles angles)
{
    float alpha;
    float beta;
    float gamma;

    alpha = angles.alpha;
    beta = angles.beta;
    gamma = angles.gamma;

    // Matrice transposée (inverse d'une rotation 3D)
    original->x = ((cosf(beta) * cosf(gamma)) * rotated.x) + ((cosf(beta) * sinf(gamma)) * rotated.y) + ((-sinf(beta)) * rotated.z);

    original->y = ((sinf(alpha) * sinf(beta) * cosf(gamma) - cosf(alpha) * sinf(gamma)) * rotated.x) + ((sinf(alpha) * sinf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma)) * rotated.y) + ((sinf(alpha) * cosf(beta)) * rotated.z);

    original->z = ((cosf(alpha) * sinf(beta) * cosf(gamma) + sinf(alpha) * sinf(gamma)) * rotated.x) + ((cosf(alpha) * sinf(beta) * sinf(gamma) - sinf(alpha) * cosf(gamma)) * rotated.y) + ((cosf(alpha) * cosf(beta)) * rotated.z);
}

extern int x;
extern int y;
static t_vector cylinder_norm(t_vector pt_on_cyl, t_object cylinder)
{
    t_vector axis;
    axis.x = 0;
    axis.y = 1;
    axis.z = 0;

    t_angles angles;
    // cylinder.direction.y = 0.3;

    find_angles(&angles, cylinder.direction, -1);

    // if (x == 1024 / 2 && y == 768 / 2)
    // printf("axis %f, %f, %f\n", axis.x, axis.y, axis.z);

    // printf("prev d %f, %f, %f >> alpha %f, %f, %f\n", cylinder.direction.x, cylinder.direction.y, cylinder.direction.z,
    // angles.alpha, angles.beta, angles.gamma);
    // printf("prev %f, %f, %f\n", axis.x, axis.y, axis.z);

    // xyz_rotation_matrix(axis, &axis, angles);

    // if (x == 1024 / 2 && y == 768 / 2)
    // {
    //     printf("axis XYZ %f, %f, %f\n", axis.x, axis.y, axis.z);

    // }
    // find_angles(&angles, cylinder.direction, -1);
    xyz_rotation_matrix_inverse(axis, &axis, angles);

    // if (x == 1024 / 2 && y == 768 / 2)
    // printf("axis ZYX %f, %f, %f\n\n", axis.x, axis.y, axis.z);

    // printf("axis %f, %f, %f\n", axis.x, axis.y, axis.z);
    // rotation_process(axis, cylinder.position, &axis, angles);

    t_vector B = axis;
    t_vector A = create_vector(&cylinder.position, &pt_on_cyl);
    t_vector Anorm = A;
    normalize_vector(&Anorm);
    // normalize_vector(&B);
    //
    float t = magnitude(A) * dot_product(&Anorm, &B);
    t_vector I;
    I.x = cylinder.position.x + (t * B.x);
    I.y = cylinder.position.y + (t * B.y);
    I.z = cylinder.position.z + (t * B.z);

    t_vector N = create_vector(&I, &pt_on_cyl);
    normalize_vector(&N);
    // if (x == 1024 / 2 && y == 768 / 2)
    //     printf("N %f, %f, %f\n\n", N.x, N.y, N.z);

    return (N);
}

void color_limit(int *color)
{
    if (*color > 255)
        *color = 255;
    // else if (*color < 0)
    //     *color = 0;
    return;
}

static void shadows(t_vector rot_pt, t_object *figure, t_world world, float L_mag, t_angles angles, t_vector rot_light,
                    t_vector pt_on_figure, int in_or_out, t_vector N, t_vector L, t_lights *diffuse_l, t_lights *specular_l,
                    t_lights *ambient_l, float cos, float t_dist, t_vector pixel, t_vector eye, t_vector ray)
{
    // if (figure->type == SPHERE)
    // return ;
    int j = -1;
    t_distances dist;
    t_vector pt_origin = pt_on_figure;
    t_vector light_ori = rot_light;
    t_vector initial_pos = figure->position;
    t_vector L_cpy = L;
    (void)ray;
    (void)pt_origin;
    (void)light_ori;
    (void)rot_pt;
    (void)initial_pos;
    while (++j < world.nb_objects)
    {

        t_object neighbour;
        neighbour = world.objects[j];

        float Ln_mag = L_mag;
        L = L_cpy;
        (void)Ln_mag;
        (void)t_dist;
        (void)pixel;

        pt_on_figure = pt_origin;
        // pt_on_figure = rot_pt;
        rot_light = world.light_position;

        dist.t1 = MAXFLOAT;
        dist.t2 = MAXFLOAT;
        // Dans le cylindre, si :
        // - on fait une ombre externe projetée par autre chose que lui-même
        // - on fait une ombre interne projetée par lui-même ou une autre figure

        if ((figure->type == CYLINDER && in_or_out == 1 && figure->index != neighbour.index)
        || (figure->type == CYLINDER && in_or_out == -1 /*&& figure->index != neighbour.index*/)
            /*|| (figure->type == CYLINDER && in_or_out == -1 && figure->index == neighbour.index)*/)
        {
            // ROTATION de la figure voisine
            if (neighbour.type == CYLINDER)
            {
                // continue;

                pt_on_figure = pt_origin;
                rot_light = world.light_position; // POUR QUE CA MARCHE SUR figure ROTE

                if (neighbour.type == CYLINDER)
                {
                    find_angles(&angles, neighbour.direction, -1);
                    rotation_process(rot_light, neighbour.position, &rot_light, angles);
                    rotation_process(pt_on_figure, neighbour.position, &pt_on_figure, angles);
                }
                // crée un vecteur roté avec les 2 points rotés
                t_vector L_n = create_vector(&pt_on_figure, &rot_light);
                Ln_mag = magnitude(L_n);
                L_mag = Ln_mag;
                normalize_vector(&L_n);

                // pour le dernier if (interieur du cylindre)
                cos = dot_product(&N, &L_n);

                (void)N;
                // !!!! Marche en remplaçant L par L_n plus loin:
                // L = create_vector(&pt_on_figure, &rot_light);
                // normalize_vector(&L);
                L = L_n;

                // if (in_or_out == -1 && figure->index == neighbour.index)
                //     dist = find_distances(L, pt_on_figure, *figure);
                // else
                dist = find_distances(L_n, pt_on_figure, neighbour);

                // if (dist.t1 == 0)
                //     dist = find_distances(L, pt_on_figure, world.objects[j]);
                // float min = fminf(dist.t1, dist.t2);
                // float max = fmaxf(dist.t1, dist.t2);
                // dist.t1 = min;
                // dist.t2 = max;
            }
            else if (neighbour.type == SPHERE)
            {

                // if (in_or_out == 1)
                // printf("1\n");
                // else
                //     printf("-1\n");
                pt_on_figure = pt_origin;
                rot_light = world.light_position;
                // le ray va de l'oeil vers le pixel
                // alors que distance va du centre vers le pixel
                // L va du point vers la lumiere
                // distance va du centre voisin vers le point
                t_vector distance = create_vector(&neighbour.position, &pt_on_figure);

                // Ln_mag = magnitude(L);
                float a = dot_product(&L, &L);
                float b = 2.0f * dot_product(&L, &distance);
                float c = dot_product(&distance, &distance) - ((neighbour.diameter / 2.0f) * (neighbour.diameter / 2.0f));
                // dist.t1 = solve_polynom(a, b, c);
                solve_poly(a, b, c, &dist);
                // dist = two_ts(a, b, c);
                // printf("!!! shpere on cylinider\n");
                // if (dist.t1 != MAXFLOAT)
                //     printf("dist.t1 != MAXFLOAT\n");
                // if (dist.t2 != MAXFLOAT)
                //     printf("dist.t2 != MAXFLOAT\n");
            }
            else if (neighbour.type == PLANE)
            {
                // continue;
                // A plane's fomrula : P is on the plane if : Norm * (P - A_plane_point) = 0.
                // It's intersection with a ray fomula : Norm * (Eye + tRay_dir - A_pl_pt)  = 0.
                // (Because the ray formula is : Eye + tRay_dir = point).
                // So, in "intersect_plane()", we use the formula :
                // t = (Norm * (A_pl_pt) - Eye) / (Norm * Ray_dir).
                t_vector on_plane = neighbour.position;
                t_vector pixel_plane = create_vector(&on_plane, &pt_on_figure);

                // on crée d'abord un vecteur plan_pt - pixel
                // ray = oeil - pixel
                dist.t2 = MAXFLOAT;
                dist.t1 = -(dot_product(&neighbour.direction, &pixel_plane)
                        / dot_product(&neighbour.direction, &L));

            }
        }
        else if (/*figure->index != neighbour.index
            &&*/ (figure->type == PLANE || figure->type == SPHERE))
        {
            // printf("figure->index %d, neighbour.index %d\n", figure->index, neighbour.index);
            // continue;

            if (neighbour.type == CYLINDER)
            {
                // continue;
                pt_on_figure = rot_pt;
                // pt_on_figure = pt_origin;
                rot_light = world.light_position; // POUR QUE CA MARCHE SUR figure ROTE

                find_angles(&angles, neighbour.direction, -1);
                rotation_process(rot_light, neighbour.position, &rot_light, angles);
                rotation_process(pt_on_figure, neighbour.position, &pt_on_figure, angles);
                // //crée un vecteur roté avec les 2 points rotés

                // L ira du point vers la lumiere
                //
                t_vector L_n = create_vector(&pt_on_figure, &rot_light);
                Ln_mag = magnitude(L_n);
                normalize_vector(&L_n);
                // // cos = dot_product(&N, &L_n);

                // (void)N;
                // // !!!! Marche en remplaçant L par L_n plus loin:
                L = L_n;

                dist = find_distances(L, pt_on_figure, neighbour);
                // if (dist.t1 == 0)
                //     dist = find_distances(L, pt_on_figure, world.objects[j]);
                // float min = fminf(dist.t1, dist.t2);
                // float max = fmaxf(dist.t1, dist.t2);
                // dist.t1 = min;
                // dist.t2 = max;

                
            }
            else if (neighbour.type == SPHERE)
            {
                pt_on_figure = rot_pt;
                rot_light = world.light_position;
                // le ray va de l'oeil vers le pixel
                // alors que distance va du centre vers le pixel
                // L va du point vers la lumiere
                // distance va du centre voisin vers le point
                t_vector distance = create_vector(&neighbour.position, &pt_on_figure);
                float a = dot_product(&L, &L);
                float b = 2.0f * dot_product(&L, &distance);
                float c = dot_product(&distance, &distance) - ((neighbour.diameter / 2.0f) * (neighbour.diameter / 2.0f));
                // dist.t1 = solve_polynom(a, b, c);
                solve_poly(a, b, c, &dist);
                // dist = two_ts(a, b, c);
            }
            else if (neighbour.type == PLANE)
            {
                // A plane's fomrula : P is on the plane if : Norm * (P - A_plane_point) = 0.
                // It's intersection with a ray fomula : Norm * (Eye + tRay_dir - A_pl_pt)  = 0.
                // (Because the ray formula is : Eye + tRay_dir = point).
                // So, in "intersect_plane()", we use the formula :
                // t = (Norm * (A_pl_pt) - Eye) / (Norm * Ray_dir).

                t_vector on_plane = neighbour.position;
                t_vector pixel_plane = create_vector(&on_plane, &pt_on_figure);

                // on crée d'abord un vecteur plan_pt - pixel
                // ray = oeil - pixel
                dist.t2 = MAXFLOAT;
                dist.t1 = -(dot_product(&neighbour.direction, &pixel_plane)
                        / dot_product(&neighbour.direction, &L));
            }
        }
        else
            continue;

        (void)cos;
        (void)in_or_out;
        (void)figure;
        (void)rot_light;
        (void)eye;
        // if (figure->type == SPHERE && neighbour.type == CYLINDER && in_or_out == 1)
        // {
        //     printf("? shpere on cylinider\n");
        //     if (dist.t1 != MAXFLOAT)
        //         printf("dist.t1 != MAXFLOAT\n");
        //     if (dist.t2 != MAXFLOAT)
        //         printf("dist.t2 != MAXFLOAT\n");
        // }

        if (
            (in_or_out == -1 && dist.t1 != MAXFLOAT && dist.t1 >= 0.01 && dist.t1 <= L_mag /*&& !cylinder_height(&neighbour, dist.t1, L,  pt_on_figure)*/)
            || (in_or_out == -1 && dist.t2 != MAXFLOAT && dist.t2 >= 0.00001 && dist.t2 <= L_mag /*&& cylinder_height(&neighbour, dist.t2, L, pt_on_figure)*/)
            // || (figure->index != neighbour.index && /*cos > 0 &&*/ in_or_out == -1 && dist.t1 != MAXFLOAT && dist.t1 >= 0.1 && dist.t1 <= L_mag && cylinder_height(&neighbour, dist.t1, L,  pt_on_figure))
            // || (figure->index != neighbour.index && /*cos > 0 &&*/ in_or_out == -1 && dist.t2 != MAXFLOAT && dist.t2 >= 0.00001 && dist.t2 <= L_mag && cylinder_height(&neighbour, dist.t2, L, pt_on_figure))
            || ((figure->index != neighbour.index && /*cos > 0 &&*/ in_or_out == 1 && dist.t1 != MAXFLOAT && dist.t1 >= 0.01 && dist.t1 <= Ln_mag /*&& !cylinder_height(&neighbour, dist.t1, L,  pt_on_figure)*/)
            || (figure->index != neighbour.index && /*cos > 0 &&*/ in_or_out == 1 && dist.t2 != MAXFLOAT && dist.t2 >= 0.00001 && dist.t2 <= Ln_mag /*&& !cylinder_height(&neighbour, dist.t2, L,  pt_on_figure)*/)))
        {

            if (neighbour.type == CYLINDER && dist.t1 != MAXFLOAT
                && dist.t1 >= 0.001 && dist.t1 <= L_mag
                && (cylinder_height(&neighbour, dist.t1, L, pt_on_figure)))
            {
                // printf("t1\n");
                
                // continue;
            }
            else if (neighbour.type == CYLINDER && dist.t2 != MAXFLOAT
                && dist.t2 >= 0.00001 && dist.t2 <= L_mag
                && (cylinder_height(&neighbour, dist.t2, L, pt_on_figure)))
            {
                // printf("t2\n");
                // ambient_l->r = 0;
                // ambient_l->g = 0;
                // ambient_l->b = 0;
                // continue;
            }
            else if ( neighbour.type == CYLINDER && dist.t1 != MAXFLOAT
                && dist.t1 >= 0.001 && dist.t1 <= L_mag
                && (!cylinder_height(&neighbour, dist.t1, L, pt_on_figure)))
                continue;
            else if (neighbour.type == CYLINDER && dist.t2 != MAXFLOAT
                && dist.t2 >= 0.00001 && dist.t2 <= L_mag
                && (!cylinder_height(&neighbour, dist.t2, L, pt_on_figure)))
                continue;

            

            specular_l->r = 0;
            specular_l->g = 0;
            specular_l->b = 0;
            diffuse_l->r = 0;
            diffuse_l->g = 0;
            diffuse_l->b = 0;

            (void)ambient_l;
            break;
        }
    }
}

t_color light_on_figure(t_vector origin_pt, t_vector pixel, t_vector rot_eye, t_vector rot_pixel, t_vector ray, float t_dist, t_object figure, t_world world,
                        int in_or_out)
{
    (void)rot_eye;
    (void)ray;
    t_color color;
    // return (figure.color);

    t_vector rot_pt = find_hit_pt(rot_pixel, ray, t_dist);
    // printf("Beginning with %f, %f, %f\n", rot_pt.x, rot_pt.y, rot_pt.z);

    t_vector N;
    t_vector rot_light = world.light_position;
    t_angles angles;

    // if (x == 1024 / 2 && y == 768 / 2)
    // printf("1- ORIGIN PT %f, %f, %f\n", origin_pt.x, origin_pt.y, origin_pt.z);

    // NORMALES
    if (figure.type == SPHERE)
    {
        // pixel = ray
        N = sphere_norm(origin_pt, figure);
        rot_pt = origin_pt;
        // return (figure.color);
    }
    else if (figure.type == CYLINDER)
    {
        N = cylinder_norm(origin_pt, figure);
        // N = cylinder_norm(origin_pt, figure);
        // rotate light
        // find_angles(&angles, figure.direction, 1);
        // rotation_process(world.light_position, origin_pt, &rot_light, angles);
        // origin_pt = rot_pt;
    }
    else if (figure.type == PLANE)
    {
        N = figure.direction;
        origin_pt = rot_pt;
        // normalize_vector(&N);
        // printf("plane N %f, %f, %f\n", N.x, N.y, N.z);
        // printf("light %f, %f, %f\n", world.light_position.x, world.light_position.y, world.light_position.z);
    }
    //////

    //  if (x == 1024 / 2 && y == 768 / 2)
    // printf("2- ORIGIN PT %f, %f, %f\n", origin_pt.x, origin_pt.y, origin_pt.z);

    t_vector L = create_vector(&origin_pt, &world.light_position); // du point vers la lumiere
    t_vector V = create_vector(&origin_pt, &pixel);                // du point vers la camera == rot_pixel ?
    // printf("L %f, %f, %f\n", L.x, L.y, L.z);

    //  if (x == 1024 / 2 && y == 768 / 2)
    // printf("3- ORIGIN PT %f, %f, %f\n", origin_pt.x, origin_pt.y, origin_pt.z);

    float L_mag = magnitude(L);
    normalize_vector(&L);
    normalize_vector(&V);

    // if (in_or_out == -1 && dot_product(&L, &N) > 0)
    // {
    N.x *= in_or_out;
    N.y *= in_or_out;
    N.z *= in_or_out;
    // }

    (void)in_or_out;

    float dot_LN = dot_product(&L, &N); // = cos de l'angle L et N
    float cos = dot_LN;
    t_vector R; // rayon réfléchi
    R.x = 2 * dot_LN * N.x - L.x;
    R.y = 2 * dot_LN * N.y - L.y;
    R.z = 2 * dot_LN * N.z - L.z;
    normalize_vector(&R);
    t_lights specular_l;
    t_lights diffuse_l;
    t_lights ambient_l;
    ambient_l.r = world.ambient_power * world.ambient_color.r;
    ambient_l.g = world.ambient_power * world.ambient_color.g;
    ambient_l.b = world.ambient_power * world.ambient_color.b;
    int shininess = 130;
    if (dot_product(&R, &V) > 0 && dot_LN > 0)
    {
        specular_l.r = powf(dot_product(&R, &V), shininess) * world.light_power * world.light_color.r;
        specular_l.g = powf(dot_product(&R, &V), shininess) * world.light_power * world.light_color.g;
        specular_l.b = powf(dot_product(&R, &V), shininess) * world.light_power * world.light_color.b;
    }
    else
    {
        specular_l.r = 0;
        specular_l.g = 0;
        specular_l.b = 0;
    }
    if (dot_LN < 0)
        dot_LN = 0;
    diffuse_l.r = dot_LN * (world.light_power * world.light_color.r);
    diffuse_l.g = dot_LN * (world.light_power * world.light_color.g);
    diffuse_l.b = dot_LN * (world.light_power * world.light_color.b);

    //  if (x == 1024 / 2 && y == 768 / 2)
    // printf("4- ORIGIN PT %f, %f, %f\n", origin_pt.x, origin_pt.y, origin_pt.z);

    // if (world.ambient_power != 1)
    shadows(rot_pt, &figure, world, L_mag, angles, rot_light, origin_pt, in_or_out, N, L, &diffuse_l,
            &specular_l, &ambient_l, cos, t_dist, rot_pixel, rot_eye, ray);

    // if (world.ambient_power == 1)
    // {
    //     specular_l.r = world.ambient_color.r ;
    //     specular_l.g = world.ambient_color.g;
    //     specular_l.b = world.ambient_color.b;
    //     diffuse_l.r = world.ambient_color.r;
    //     diffuse_l.g = world.ambient_color.g;
    //     diffuse_l.b = world.ambient_color.b;
    //     world.light_power = 1;
    // }

    color.r = figure.color.r * ((ambient_l.r + diffuse_l.r + specular_l.r) / 255.f);
    color_limit(&color.r);
    color.g = figure.color.g * ((ambient_l.g + diffuse_l.g + specular_l.g) / 255.f);
    color_limit(&color.g);
    color.b = figure.color.b * ((ambient_l.b + diffuse_l.b + specular_l.b) / 255.f);
    color_limit(&color.b);

    // color.r = figure.color.r + ((ambient_l.r + diffuse_l.r + specular_l.r));
    // color_limit(&color.r);
    // color.g = figure.color.g + ((ambient_l.g + diffuse_l.g + specular_l.g));
    // color_limit(&color.g);
    // color.b = figure.color.b + ((ambient_l.b + diffuse_l.b + specular_l.b));
    // color_limit(&color.b);

    return (color);
}