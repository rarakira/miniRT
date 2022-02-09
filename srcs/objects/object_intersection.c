/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/09 18:41:38 by lbaela           ###   ########.fr       */
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
		spec = calc_rgb_light(light->rgb, 0.6 * strength);
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

float	vect_dist(t_vector v1, t_vector v2)
{
	float	res;

	res = (v1.x - v2.x) * (v1.x - v2.x)
		+ (v1.y - v2.y) * (v1.y - v2.y)
		+ (v1.z - v2.z) * (v1.z - v2.z);
	return (res);
}

int	intersection_exists(t_object **objs, t_point *point)
{
	t_vector	origin;
	t_vector	ray;
	float		res;
	int			i;

	i = 0;
	point->dist = MAX_DIST;
	ray = point->norm_v;
	origin = point->hit_coord;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res = sphere_intersects(&origin, objs[i], &ray);
		else if (objs[i]->type == 'C')
			res = cylinder_intersects(&origin, objs[i], &ray);
		else if (objs[i]->type == 'P')
			res = plane_intersects(&origin, objs[i], &ray);
		if (res != 0 && res < point->dist)
			point->dist = res;
		i++;
	}
	if (point->dist == MAX_DIST)
		return (0);
	return (point->dist);
}

int	in_shadow(t_minirt *minirt, t_point *point, t_light *light)
{
	t_point		intersect;
	float		dist_to_light;
	float		dist_to_obj;

	intersect.hit_coord = vect_mult(&point->norm_v, 0.0001);
	intersect.hit_coord = vect_add(&point->hit_coord, &intersect.hit_coord);
	// intersect.hit_coord = vect_add(&point->hit_coord, &point->norm_v);
	intersect.norm_v = vect_substract(light->point, &intersect.hit_coord);
	normalise_vect(&intersect.norm_v);
	if (intersection_exists(minirt->objs, &intersect))
	{
		dist_to_light = vect_dist(point->hit_coord, *light->point);
		dist_to_obj = vect_dist(point->hit_coord, intersect.hit_coord);
		if (dist_to_obj < dist_to_light)
			return (1);
	}
	return (0);
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
			res = sphere_intersects(minirt->camera->origin, objs[i], ray);
		else if (objs[i]->type == 'C')
			res = cylinder_intersects(minirt->camera->origin, objs[i], ray);
		else if (objs[i]->type == 'P')
			res = plane_intersects(minirt->camera->origin, objs[i], ray);
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
