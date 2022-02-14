/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/14 17:43:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../../includes/minirt.h"
#include "../../includes/objects.h"

t_vector	get_hit_direction(t_object *obj, t_vector ray)
{
	if (obj->type == 'S')
		obj->hit_norm_v = vect_substract(obj->hit_point, *obj->center);
	else if (obj->type == 'C')
	{
		obj->is_inside = 0;
	}
	else if (obj->type == 'P')
	{
		obj->is_inside = 0;
		obj->hit_norm_v = *obj->norm_v;
		if (vect_dot_product(ray, *obj->norm_v) > 0.0)
			obj->hit_norm_v = vect_mult(obj->hit_norm_v, -1);
	}
	if (obj->is_inside)
		obj->hit_norm_v = vect_mult(obj->hit_norm_v, -1);
	normalise_vect(&obj->hit_norm_v);
	return (obj->hit_norm_v);
}

inline static void	update_point_colour(t_minirt *minirt, t_point *point, t_object *obj, t_vector ray)
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
	if (in_shadow(minirt, point, minirt->light))
	{
		point->rgb = multiply_rgbs(point->rgb,
				calc_rgb_light(minirt->ambient->rgb,
					minirt->ambient->lighting_ratio));
		point->colour = ft_rgb_hex(0, point->rgb);
		return ;
	}
	add_light(minirt, point);
	add_specular(ray, point, minirt->light);
}

void	object_intersects(	t_minirt *minirt,
							t_object **objs, t_vector ray, t_point *point)
{
	int			i;
	float		res;

	i = 0;
	point->obj = NULL;
	point->dist = MAX_DIST;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res = sphere_intersects(*minirt->camera->origin, objs[i], ray);
		else if (objs[i]->type == 'C')
			res = cylinder_intersects(*minirt->camera->origin, objs[i], ray);
		else if (objs[i]->type == 'P')
			res = plane_intersects(*minirt->camera->origin, objs[i], ray);
		if (res != 0 && res < point->dist)
		{
			point->obj = objs[i];
			point->dist = res;
		}
		i++;
	}
	update_point_colour(minirt, point, point->obj, ray);
}
