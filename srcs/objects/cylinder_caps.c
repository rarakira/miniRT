/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 20:11:05 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/minirt.h"

static int	solve_caps(t_eq *caps, t_object *obj, t_vector ray)
{
	short		res[2];
	t_vector	cap_c[2];
	t_vector	hit[2];

	ft_memset(&res, 0, sizeof(res));
	if (caps->dist1 >= MIN_DIST)
	{
		hit[0] = vect_mult(ray, caps->dist1);
		cap_c[0] = vect_add(obj->center, vect_mult(obj->norm_v, caps->m1));
		res[0] = (fabs(point_dist(hit[0], cap_c[0])) <= obj->radius);
	}
	if (caps->dist2 >= MIN_DIST)
	{
		hit[1] = vect_mult(ray, caps->dist2);
		cap_c[1] = vect_add(obj->center, vect_mult(obj->norm_v, caps->m2));
		res[1] = (fabs(point_dist(hit[1], cap_c[1])) <= obj->radius);
	}
	if (!res[0] && !res[1])
		return (0);
	if ((res[0] && res[1] && caps->dist2 < caps->dist1) || !res[0])
	{
		caps->dist1 = caps->dist2;
		caps->m1 = caps->m2;
	}
	return (1);
}

int	get_cylinder_caps(t_eq *caps, t_object *obj, t_vector ray, t_vector origin)
{
	float		dot_r_nv;
	t_vector	orig_pl1;
	t_vector	orig_pl2;

	normalise_vect(&obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	caps->m1 = obj->height;
	caps->m2 = -obj->height;
	orig_pl1 = vect_substract(origin,
			vect_add(obj->center, vect_mult(obj->norm_v, caps->m1)));
	orig_pl2 = vect_substract(origin,
			vect_add(obj->center, vect_mult(obj->norm_v, caps->m2)));
	caps->dist1 = -vect_dot_product(orig_pl1, obj->norm_v) / dot_r_nv;
	caps->dist2 = -vect_dot_product(orig_pl2, obj->norm_v) / dot_r_nv;
	if (caps->dist1 < MIN_DIST && caps->dist2 < MIN_DIST)
		return (0);
	return (solve_caps(caps, obj, ray));
}

int	get_cone_cap(t_eq *cap, t_object *obj, t_vector ray, t_vector origin)
{
	float		dot_r_nv;
	t_vector	orig_pl;

	normalise_vect(&obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	cap->m1 = obj->height;
	orig_pl = vect_substract(origin,
			vect_add(obj->center, vect_mult(obj->norm_v, cap->m1)));
	cap->dist1 = -vect_dot_product(orig_pl, obj->norm_v) / dot_r_nv;
	if (cap->dist1 < MIN_DIST)
		return (0);
	cap->dist2 = -1;
	return (solve_caps(cap, obj, ray));
}
