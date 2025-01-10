/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayzatov <jayzatov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:58:49 by jayzatov          #+#    #+#             */
/*   Updated: 2025/01/10 13:08:34 by jayzatov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lights.h>

// static void shadows(t_vector rot_pt, t_object *figure, t_world world, double L_mag, t_angles angles, t_vector rot_light,
//                     t_vector pt_on_figure, int in_or_out, t_vector N, t_vector L, t_lights *diffuse_l, t_lights *specular_l,
//                     t_lights *ambient_l, double cos, double t_dist, t_vector pixel, t_vector eye, t_vector ray)
// {
//     int j = -1;
//     t_distances dist;
//     t_vector pt_origin = pt_on_figure;
//     t_vector light_ori = rot_light;
//     t_vector initial_pos = figure->position;
//     t_vector L_cpy = L;
//     (void)ray;
//     (void)pt_origin;
//     (void)light_ori;
//     (void)rot_pt;
//     (void)initial_pos;
//     while (++j < world.nb_objects)
//     {

//         t_object neighbour;
//         neighbour = world.objects[j];

//         L = L_cpy;
//         double Ln_mag = L_mag;
//         (void)t_dist;
//         (void)pixel;

//         pt_on_figure = pt_origin;
//         rot_light = world.light_position;

//         dist.t1 = MAXFLOAT;
//         dist.t2 = MAXFLOAT;
//         if ((outside(in_or_out, figure, neighbour)
//             || inside(in_or_out)))
//         {
//             if (neighbour.type == CYLINDER)
//             {
//                 pt_on_figure = pt_origin;
//                 rot_light = world.light_position; // POUR QUE CA MARCHE SUR figure ROTE

//                 find_angles(&angles, neighbour.direction, -1);
//                 rotation_process(rot_light, neighbour.position, &rot_light, angles);
//                 rotation_process(pt_on_figure, neighbour.position, &pt_on_figure, angles);
            
//                 // crée un vecteur roté avec les 2 points rotés
//                 t_vector L_n = create_vector(&pt_on_figure, &rot_light);
//                 Ln_mag = magnitude(L_n);
//                 L_mag = Ln_mag;
//                 normalize_vector(&L_n);

//                 // pour le dernier if (interieur du cylindre)
//                 cos = dot_product(&N, &L_n);

//                 (void)N;
//                 // !!!! Marche en remplaçant L par L_n plus loin:
//                 // L = create_vector(&pt_on_figure, &rot_light);
//                 // normalize_vector(&L);
//                 L = L_n;

//                 // if (in_or_out == -1 && figure->index == neighbour.index)
//                 //     dist = find_distances(L, pt_on_figure, *figure);
//                 // else
//                 dist = find_distances(L_n, pt_on_figure, neighbour);

//                 // if (dist.t1 == 0)
//                 //     dist = find_distances(L, pt_on_figure, world.objects[j]);
//                 // double min = fmin(dist.t1, dist.t2);
//                 // double max = fmax(dist.t1, dist.t2);
//                 // dist.t1 = min;
//                 // dist.t2 = max;
//             }
//             else if (neighbour.type == SPHERE)
//             {

//                 // if (in_or_out == 1)
//                 // printf("1\n");
//                 // else
//                 //     printf("-1\n");
//                 pt_on_figure = pt_origin;
//                 rot_light = world.light_position;
//                 // le ray va de l'oeil vers le pixel
//                 // alors que distance va du centre vers le pixel
//                 // L va du point vers la lumiere
//                 // distance va du centre voisin vers le point
//                 t_vector distance = create_vector(&neighbour.position, &pt_on_figure);

//                 // Ln_mag = magnitude(L);
//                 double a = dot_product(&L, &L);
//                 double b = 2.0 * dot_product(&L, &distance);
//                 double c = dot_product(&distance, &distance) - ((neighbour.diameter / 2.0) * (neighbour.diameter / 2.0));
//                 // dist.t1 = solve_polynom(a, b, c);
//                 solve_poly(a, b, c, &dist);
//                 // dist = two_ts(a, b, c);
//                 // printf("!!! shpere on cylinider\n");
//                 // if (dist.t1 != MAXFLOAT)
//                 //     printf("dist.t1 != MAXFLOAT\n");
//                 // if (dist.t2 != MAXFLOAT)
//                 //     printf("dist.t2 != MAXFLOAT\n");
//             }
//             else if (neighbour.type == PLANE)
//             {
//                 // continue;
//                 // A plane's fomrula : P is on the plane if : Norm * (P - A_plane_point) = 0.
//                 // It's intersection with a ray fomula : Norm * (Eye + tRay_dir - A_pl_pt)  = 0.
//                 // (Because the ray formula is : Eye + tRay_dir = point).
//                 // So, in "intersect_plane()", we use the formula :
//                 // t = (Norm * (A_pl_pt) - Eye) / (Norm * Ray_dir).
//                 t_vector on_plane = neighbour.position;
//                 t_vector pixel_plane = create_vector(&on_plane, &pt_on_figure);

//                 // on crée d'abord un vecteur plan_pt - pixel
//                 // ray = oeil - pixel
//                 dist.t2 = MAXFLOAT;
//                 dist.t1 = -(dot_product(&neighbour.direction, &pixel_plane)
//                         / dot_product(&neighbour.direction, &L));

//             }
//         }
//         else
//             continue;

//         (void)cos;
//         (void)in_or_out;
//         (void)figure;
//         (void)rot_light;
//         (void)eye;
        
//         double t = MAXFLOAT;
//         if ((inside(in_or_out) && t1_limits(dist.t1, Ln_mag))
//             || (outside(in_or_out, figure, neighbour) && t1_limits(dist.t1, Ln_mag)))
//             t = dist.t1;
       
//         else if ((inside(in_or_out) && t2_limits(dist.t2, Ln_mag))
//             || (outside(in_or_out, figure, neighbour) && t2_limits(dist.t2, Ln_mag)))
//             t = dist.t2;
        
//         else
//             continue;
        
//         if (t != MAXFLOAT)
//         {
//             if (neighbour.type == CYLINDER
//                 && not_cyl_height(t, neighbour, dist, L, pt_on_figure, Ln_mag))
//                 continue;
                     
//             specular_l->r = 0;
//             specular_l->g = 0;
//             specular_l->b = 0;
//             diffuse_l->r = 0;
//             diffuse_l->g = 0;
//             diffuse_l->b = 0;
           
//             (void)ambient_l;
//             break;
//         }
//     }
// }
