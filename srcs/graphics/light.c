/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:20:51 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 17:26:19 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../../includes/minirt.h"

static t_rgb	add_diff_light(t_light *light, t_point *point)
{
	float		intens;
	t_vector	l_len;

	l_len = vect_substract(light->point, point->hit_coord);
	intens = light->brightness * fmax(point->dist, 0)
		* (10 / vect_len(l_len));
	return (calc_rgb_light(light->rgb, intens));
}

static t_rgb	add_specular(t_vector ray, t_point *point, t_light *light)
{
	t_vector	half_vect;
	t_vector	to_cam;
	double		strength;
	float		r_dot_v;

	to_cam = vect_mult(ray, -1);
	normalise_vect(&to_cam);
	half_vect = vect_add(point->light_dir, to_cam);
	normalise_vect(&half_vect);
	r_dot_v = vect_dot_product(half_vect, point->norm_v);
	strength = light->brightness * pow(fmax(r_dot_v, 0.0), 100);
	return (calc_rgb_light(light->rgb, 0.6 * strength));
}

static int	intersection_exists(	t_object **objs,
									t_point *intx, t_object *current)
{
	float		res;
	int			i;

	i = 0;
	res = 0;
	intx->dist = INFINITY;
	while (objs[i] != NULL)
	{
		if (current != objs[i] && objs[i]->type == SPHERE)
			res = sphere_intersects(intx->hit_coord, objs[i], intx->norm_v);
		else if (current != objs[i] && objs[i]->type == CYLINDER)
			res = cylinder_intersects(intx->hit_coord, objs[i], intx->norm_v);
		else if (current != objs[i] && objs[i]->type == PLANE)
			res = plane_intersects(intx->hit_coord, objs[i], intx->norm_v);
		else if (current != objs[i] && objs[i]->type == CONE)
			res = cone_intersects(intx->hit_coord, objs[i], intx->norm_v);
		if (res != 0.0 && res < intx->dist)
			intx->dist = res;
		i++;
	}
	if (intx->dist == INFINITY)
		return (0);
	intx->hit_coord = vect_add(vect_mult(intx->norm_v, intx->dist),
			intx->hit_coord);
	return (1);
}

static int	in_shadow(t_scene *scene, t_point *point, t_light *light)
{
	t_point		intersect;
	float		dist_to_light;
	float		dist_to_obj;

	intersect.hit_coord = vect_add(point->hit_coord,
			vect_mult(point->norm_v, 0.00001));
	intersect.norm_v = vect_substract(light->point, intersect.hit_coord);
	normalise_vect(&intersect.norm_v);
	if (intersection_exists(scene->objs, &intersect, point->obj))
	{
		dist_to_light = point_dist(point->hit_coord, light->point);
		dist_to_obj = point_dist(point->hit_coord, intersect.hit_coord);
		if (dist_to_obj < dist_to_light)
			return (1);
	}
	return (0);
}

void	update_point_color(t_scene *scene, t_point *point, t_vector ray)
{
	t_rgb		color;
	int			i;

	i = 0;
	color = calc_rgb_light(scene->ambient.rgb, scene->ambient.brightness);
	while (scene->lights[i])
	{
		point->light_dir = vect_substract(scene->lights[i]->point,
				point->hit_coord);
		normalise_vect(&point->light_dir);
		point->dist = vect_dot_product(point->norm_v, point->light_dir);
		if (!in_shadow(scene, point, scene->lights[i]))
		{
			if (point->dist > 0.0)
				color = add_rgb_light(
						add_diff_light(scene->lights[i], point), color);
			color = add_rgb_light(
					add_specular(ray, point, scene->lights[i]), color);
		}
		i++;
	}
	point->rgb = multiply_rgbs(point->rgb, color);
	point->color = ft_rgb_hex(0, point->rgb);
}
