/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 20:50:08 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../includes/minirt.h"
#include "../../includes/objects.h"

static void	add_light(t_minirt *minirt, t_point *point)
{
	float		light;
	float		n_dot_l;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_vector	l_len;

	/* add ambient lighting */
	light = minirt->ambient->lighting_ratio;
	ambient = calc_rgb_light(minirt->ambient->rgb, light);
	/* add diffuse lighting */
	l_len = vect_substract(minirt->light->point, &point->hit_coord);
	n_dot_l = vect_dot_product(&point->norm_v, minirt->light->point);
	if (n_dot_l <= 0.0 && point->type == 'P')
	{
		point->norm_v = vect_mult(&point->norm_v, -1.0);
		n_dot_l *= -1.0;
	}
	if (n_dot_l > 0.0)
	{
		light = minirt->light->brightness_ratio * n_dot_l
			/ (vect_len(&point->norm_v) * vect_len(&l_len));
		diffuse = calc_rgb_light(minirt->light->rgb, light);
		ambient = add_rgb_light(ambient, diffuse);
	}
	point->rgb = multiply_rgbs(point->rgb, ambient);
	point->colour = ft_rgb_hex(0, point->rgb);
}

static void	add_specular(t_vector *ray, t_point *point, t_light *light)
{
	t_vector	reflect;
	t_rgb		spec;
	double		strength;
	float		r_dot_v;

	reflect = reflect_vector(vect_mult(light->point, -1.0), point->norm_v);
	r_dot_v = vect_dot_product(&reflect, ray);
	if (r_dot_v > 0.0)
	{
		strength = light->brightness_ratio
			* pow(r_dot_v / vect_len(&reflect) * vect_len(ray), 32);
		spec = calc_rgb_light(light->rgb, 0.5 * strength);
		point->colour = ft_rgb_hex(0, add_rgb_light(point->rgb, spec));
	}
}

inline static void	update_point(t_point *point, t_object *obj)
{
	if (obj == NULL)
	{
		point->colour = COL_BLACK;
		return ;
	}
	point->rgb = obj->rgb;
	point->colour = obj->colour;
	point->norm_v = obj->hit_norm_v;
	point->hit_coord = obj->hit_point;
	point->type = obj->type;
}

void	object_intersects(	t_minirt *minirt,
							t_object **objs, t_vector *ray, t_point *point)
{
	int			i;
	float		res;

	i = 0;
	point->obj = NULL;
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
			point->obj = objs[i];
			point->dist = res;
		}
		i++;
	}
	update_point(point, point->obj);
	if (point->obj == NULL)
		return ;
	add_light(minirt, point);
	add_specular(ray, point, minirt->light);
}
