/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/03 10:17:50 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "../../includes/minirt.h"
#include "../../includes/objects.h"

// void	computelighting(P, N, V, s) {
// 	int	i = 0;

// 	for light in scene.Lights
// 	{
// 		if (light.type == ambient)
// 		{
// 			i += light.intensity;
// 		}
// 		else
// 		{
// 			if (light.type == point)
// 			{
// 				L = light.position - P;
// 			} else {
// 				L = light.direction;
// 			}

// 			// Diffuse
// 			n_dot_l = dot(N, L)
// 			if n_dot_l > 0 {
// 				i += light.intensity * n_dot_l/(length(N) * length(L))
// 			}

// 			// Specular
// 		if s != -1 {
// 				R = 2 * N * dot(N, L) - L
// 				r_dot_v = dot(R, V)
// 			if r_dot_v > 0 {
// 					i += light.intensity * pow(r_dot_v/(length(R) * length(V)), s)
// 				}
// 			}
// 		}
// 	}
// 	return i
// }

t_rgb	calc_rgb_light(t_rgb colour, double light)
{
	t_rgb	new;

	new.r = (int)((double)colour.r * light);
	new.g = (int)((double)colour.g * light);
	new.b = (int)((double)colour.b * light);
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return (new);
}

t_rgb	add_rgb_light(t_rgb a, t_rgb b)
{
	t_rgb	colour;

	colour.r = a.r + b.r;
	colour.g = a.g + b.g;
	colour.b = a.b + b.b;
	if (colour.r > 255)
		colour.r = 255;
	if (colour.g > 255)
		colour.g = 255;
	if (colour.b > 255)
		colour.b = 255;
	return (colour);
}

void	add_light(t_minirt *minirt, t_point *point)
{
	float		light;
	float		n_dot_l;
	t_rgb		al_rgb;
	t_rgb		l_rgb;
	t_vector	l_len;

	/* add ambient lighting */
	light = minirt->ambient->lighting_ratio;
	point->rgb = calc_rgb_light(point->rgb, light);
	al_rgb = calc_rgb_light(minirt->ambient->rgb, light);
	al_rgb = add_rgb_light(point->rgb, al_rgb);
	/* add diffuse lighting */
	l_len = vect_substract(minirt->light->point, &point->hit_coord);
	n_dot_l = vect_dot_product(&point->norm_v, minirt->light->point);
	if (n_dot_l > 0.1)
	{
		light = minirt->light->brightness_ratio * n_dot_l
			/ (vect_len(&point->norm_v) * vect_len(&l_len));
		l_rgb = calc_rgb_light(minirt->light->rgb, light);
		al_rgb = add_rgb_light(al_rgb, l_rgb);
	}
	point->rgb = add_rgb_light(point->rgb, al_rgb);
	point->colour = ft_rgb_hex(0, point->rgb);
}

void	object_intersects(	t_minirt *minirt,
							t_object **objs, t_vector *ray, t_point *point)
{
	int			i;
	float		res;

	i = 0;
	point->colour = COL_BLACK;
	point->dist = MAX_DIST;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res = sphere_intersects(minirt->camera, objs[i], ray);
		else if (objs[i]->type == 'C')
			res = cylinder_intersects(minirt->camera, objs[i], ray);
		else if (objs[i]->type == 'P')
			res = plane_intersects(minirt->camera, objs[i], ray);
		if (res != 0 && res < point->dist)
		{
			point->dist = res;
			point->rgb = objs[i]->rgb;
			point->colour = objs[i]->colour;
			point->norm_v = objs[i]->hit_norm_v;
			point->hit_coord = objs[i]->hit_point;
		}
		i++;
	}
	if (point->colour != COL_BLACK)
		add_light(minirt, point);
}
