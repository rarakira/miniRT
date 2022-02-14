/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/14 14:51:21 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/parsing.h"

static int	in_range(float num, float range)
{
	if (num < -range)
		return (0);
	if (num > range)
		return (0);
	return (1);
}

static int	get_caps(t_eq *caps, t_object *obj, t_vector ray)
{
	float		dot_r_nv;
	t_vector	orig_pl1;
	t_vector	orig_pl2;
	short		res[2];
	t_vector	hit[2];

	normalise_vect(obj->norm_v);
	dot_r_nv = vect_dot_product(ray, *obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	caps->m1 = obj->height;
	caps->m2 = -obj->height;
	orig_pl1 = vect_substract((t_vector){0, 0, 0},
			vect_add(*obj->center, vect_mult(*obj->norm_v, caps->m1)));
	orig_pl2 = vect_substract((t_vector){0, 0, 0},
			vect_add(*obj->center, vect_mult(*obj->norm_v, caps->m2)));
	caps->dist1 = -vect_dot_product(orig_pl1, *obj->norm_v) / dot_r_nv;
	caps->dist2 = -vect_dot_product(orig_pl2, *obj->norm_v) / dot_r_nv;
	if (caps->dist1 < MIN_DIST && caps->dist2 < MIN_DIST)
		return (0);
	if (caps->dist1 >= MIN_DIST)
	{
		hit[0] = vect_mult(ray, caps->dist1);
		orig_pl1 = vect_add(*obj->center, vect_mult(*obj->norm_v, caps->m1));
	}
	if (caps->dist2 >= MIN_DIST)
	{
		hit[1] = vect_mult(ray, caps->dist2);
		orig_pl2 = vect_add(*obj->center, vect_mult(*obj->norm_v, caps->m2));
	}
	res[0] = (caps->dist1 >= MIN_DIST && fabs(point_distance(hit[0], orig_pl1)) <= obj->radius);
	res[1] = (caps->dist2 >= MIN_DIST && fabs(point_distance(hit[1], orig_pl2)) <= obj->radius);
	if (!res[0] && !res[1])
		return (0);
	if ((res[0] && res[1] && caps->dist2 < caps->dist1) || !res[0])
	{
		caps->dist1 = caps->dist2;
		caps->m1 = caps->m2;
	}
	return (1);
}

static float	get_distance(t_object *obj, t_vector ray, t_eq body)
{
	t_eq	caps;

	ft_memset(&caps, 0, sizeof(t_eq));
	if (in_range(body.m1, obj->height) && in_range(body.m2, obj->height))
	{
		obj->dist = body.dist1;
		obj->m = body.m1;
		if (body.dist1 > body.dist2)
			obj->dist = body.dist2;
		if (body.dist1 > body.dist2)
			obj->m = body.m2;
	}
	else
	{
		if (!get_caps(&caps, obj, ray) && !in_range(body.m1, obj->height) && !in_range(body.m2, obj->height))
			return (0);
		if (in_range(body.m1, obj->height) && (body.dist1 < caps.dist1 || caps.dist1 < MIN_DIST)) // 
		{
			obj->dist = body.dist1;
			obj->m = body.m1;
		}
		else if (in_range(body.m2, obj->height) &&  (body.dist2 < caps.dist1 || caps.dist1 < MIN_DIST))
		{
			obj->dist = body.dist2;
			obj->m = body.m2;
		}
		else
		{
			obj->dist = caps.dist1;
			obj->m = caps.m1;
			obj->hit_point = vect_mult(ray, obj->dist);
			obj->hit_norm_v = *obj->norm_v;
			if (vect_dot_product(ray, *obj->norm_v) > 0.0)
				obj->hit_norm_v = vect_mult(obj->hit_norm_v, -1);
			normalise_vect(&obj->hit_norm_v);
			return (obj->dist);
		}
	}
	obj->hit_point = vect_mult(ray, obj->dist);
	obj->hit_norm_v = vect_substract(obj->hit_point, *obj->center);
	obj->hit_norm_v = vect_substract(obj->hit_norm_v,
			vect_mult(*obj->norm_v, obj->m));
	normalise_vect(&obj->hit_norm_v);
	return (obj->dist);
}

static inline float	find_dists_cy(	t_object *obj,
									t_vector orig_cyl, t_vector ray, t_eq eq)
{
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.discr = sqrt(eq.discr);
	eq.dist1 = (-eq.b - eq.discr) / (2 * eq.a);
	eq.dist2 = (-eq.b + eq.discr) / (2 * eq.a);
	eq.m1 = vect_dot_product(ray, *obj->norm_v) * eq.dist1
		+ vect_dot_product(orig_cyl, *obj->norm_v);
	eq.m2 = vect_dot_product(ray, *obj->norm_v) * eq.dist2
		+ vect_dot_product(orig_cyl, *obj->norm_v);
	if (eq.dist1 <= MIN_DIST)
		eq.m1 = obj->height + 1.0;
	if (eq.dist2 <= MIN_DIST)
		eq.m2 = obj->height + 1.0;
	return (get_distance(obj, ray, eq));
}

float	cylinder_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	t_vector	orig_cyl;
	t_eq		eq;
	float		dot_r_nv;
	float		dot_cc_nv;

	orig_cyl = vect_substract(origin, *obj->center);
	normalise_vect(obj->norm_v);
	dot_r_nv = vect_dot_product(ray, *obj->norm_v);
	dot_cc_nv = vect_dot_product(orig_cyl, *obj->norm_v);
	eq.a = vect_dot_product(ray, ray)
		- dot_r_nv * dot_r_nv;
	eq.b = 2 * (vect_dot_product(ray, orig_cyl) - dot_r_nv * dot_cc_nv);
	eq.c = vect_dot_product(orig_cyl, orig_cyl)
		- dot_cc_nv * dot_cc_nv - obj->radius * obj->radius;
	return (find_dists_cy(obj, orig_cyl, ray, eq));
}

void	ft_read_cylinder(t_minirt *minirt, char *line)
{
	int	i;

	i = 2;
	minirt->objs_lst->type = 'C';
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->center->x = ft_atof(line, &i);
	minirt->objs_lst->center->y = ft_atof(line, &i);
	minirt->objs_lst->center->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->norm_v->x = ft_atof(line, &i);
	minirt->objs_lst->norm_v->y = ft_atof(line, &i);
	minirt->objs_lst->norm_v->z = ft_atof(line, &i);
	normalise_vect(minirt->objs_lst->norm_v);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->radius = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->height = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.b = ft_atoi(&line[++i]);
	minirt->objs_lst->colour = ft_rgb_hex(0, minirt->objs_lst->rgb);
}
