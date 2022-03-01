/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 18:14:12 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "../../includes/minirt.h"

static void	get_hit_cy_co(t_object *obj)
{
	if ((obj->type == CYLINDER || obj->type == CONE)
		&& obj->hit.type == BODY)
	{
		obj->hit.norm_v = vect_substract(
				vect_substract(obj->hit.point, obj->center),
				vect_mult(obj->norm_v, obj->hit.m));
	}
	if (obj->type == CONE && obj->hit.type == BODY)
	{
		obj->hit.norm_v = vect_substract(obj->hit.norm_v,
				vect_mult(obj->norm_v, tan(obj->radius / obj->height)
					* tan(obj->radius / obj->height) * obj->hit.m));
	}
}

t_vector	get_hit_direction(t_object *obj, t_vector ray)
{
	obj->hit.point = vect_mult(ray, obj->hit.dist);
	if (obj->type == SPHERE)
		obj->hit.norm_v = vect_substract(obj->hit.point, obj->center);
	else if ((obj->type == CYLINDER || obj->type == CONE)
		&& obj->hit.type == BODY)
		get_hit_cy_co(obj);
	else if (obj->type == PLANE || obj->hit.type == CAP)
	{
		obj->hit.norm_v = obj->norm_v;
		if (vect_dot_product(ray, obj->norm_v) > 0.0)
			obj->hit.is_inside = 1;
	}
	if (obj->hit.is_inside)
		obj->hit.norm_v = vect_mult(obj->hit.norm_v, -1);
	normalise_vect(&obj->hit.norm_v);
	return (obj->hit.norm_v);
}

inline static void	update_point_vals(	t_minirt *minirt, t_point *point,
										t_object *obj, t_vector ray)
{
	if (obj == NULL)
	{
		point->color = COL_BLACK;
		return ;
	}
	point->rgb = obj->rgb;
	if (obj->type == SPHERE)
	{
		if (minirt->apply_checkerboard)
			point->rgb = ft_checkerboard(obj, point);
		if (minirt->apply_texture || minirt->apply_bump)
			point->rgb = ft_pattern(obj, ray, minirt);
	}
	point->color = ft_rgb_hex(0, point->rgb);
	if (obj->type == LIGHT)
		return ;
	point->norm_v = get_hit_direction(obj, ray);
	point->hit_coord = obj->hit.point;
	point->type = obj->type;
	update_point_color(&minirt->scene, point, ray);
}

t_object	*object_intersects(t_minirt *minirt,
							t_object **objs, t_vector ray, t_point *point)
{
	int			i;
	float		res;

	i = 0;
	point->obj = NULL;
	point->dist = INFINITY;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == SPHERE || objs[i]->type == LIGHT)
			res = sphere_intersects(minirt->scene.camera.point, objs[i], ray);
		else if (objs[i]->type == CYLINDER)
			res = cylinder_intersects(minirt->scene.camera.point, objs[i], ray);
		else if (objs[i]->type == PLANE)
			res = plane_intersects(minirt->scene.camera.point, objs[i], ray);
		else if (objs[i]->type == CONE)
			res = cone_intersects(minirt->scene.camera.point, objs[i], ray);
		if (res != 0 && res < point->dist)
		{
			point->obj = objs[i];
			point->dist = res;
		}
		i++;
	}
	update_point_vals(minirt, point, point->obj, ray);
	return (point->obj);
}
