/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 08:04:12 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 20:10:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/minirt.h"

static int	in_range(float num, float range)
{
	if (num < 0)
		return (0);
	if (num > range)
		return (0);
	return (1);
}

static void	update_hit_point(t_intersection *hit, float dist, float m)
{
	hit->dist = dist;
	hit->m = m;
}

static float	get_dist(	t_object *obj,
							t_vector ray, t_eq body, t_vector origin)
{
	t_eq	cap;

	ft_memset(&cap, 0, sizeof(t_eq));
	if (!get_cone_cap(&cap, obj, ray, origin)
		&& !in_range(body.m1, obj->height)
		&& !in_range(body.m2, obj->height))
		return (0);
	if (in_range(body.m1, obj->height) && (body.dist1 < cap.dist1))
		update_hit_point(&obj->hit, body.dist1, body.m1);
	else if (in_range(body.m2, obj->height) && (body.dist2 < cap.dist1))
		update_hit_point(&obj->hit, body.dist2, body.m2);
	else
	{
		obj->hit.type = CAP;
		update_hit_point(&obj->hit, cap.dist1, cap.m1);
	}
	return (obj->hit.dist);
}

static inline float	find_dists_co(	t_object *obj,
									t_vector ray, t_eq eq, t_vector origin)
{
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.discr = sqrt(eq.discr);
	eq.dist1 = (-eq.b - eq.discr) / (2 * eq.a);
	eq.dist2 = (-eq.b + eq.discr) / (2 * eq.a);
	if (eq.dist1 <= MIN_DIST && eq.dist2 <= MIN_DIST)
		return (0);
	eq.m1 = vect_dot_product(ray, obj->norm_v) * eq.dist1
		+ vect_dot_product(vect_substract(origin, obj->center), obj->norm_v);
	eq.m2 = vect_dot_product(ray, obj->norm_v) * eq.dist2
		+ vect_dot_product(vect_substract(origin, obj->center), obj->norm_v);
	if (eq.dist1 <= MIN_DIST)
		eq.m1 = -1.0;
	if (eq.dist2 <= MIN_DIST)
		eq.m2 = -1.0;
	obj->hit.type = BODY;
	if (in_range(eq.m1, obj->height) && in_range(eq.m2, obj->height))
	{
		update_hit_point(&obj->hit, eq.dist1, eq.m1);
		if (eq.dist1 > eq.dist2)
			update_hit_point(&obj->hit, eq.dist2, eq.m2);
		return (obj->hit.dist);
	}
	return (get_dist(obj, ray, eq, origin));
}

float	cone_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	t_vector	orig_co;
	t_eq		eq;
	float		dot_r_nv;
	float		dot_cc_nv;
	float		tan_ha;

	obj->hit.is_inside = 0;
	orig_co = vect_substract(origin, obj->center);
	normalise_vect(&obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	dot_cc_nv = vect_dot_product(orig_co, obj->norm_v);
	tan_ha = 1 + tan(obj->radius / obj->height)
		* tan(obj->radius / obj->height);
	eq.a = vect_dot_product(ray, ray) - tan_ha * dot_r_nv * dot_r_nv;
	eq.b = 2 * (vect_dot_product(ray, orig_co) - tan_ha * dot_r_nv * dot_cc_nv);
	eq.c = vect_dot_product(orig_co, orig_co) - tan_ha * dot_cc_nv * dot_cc_nv;
	return (find_dists_co(obj, ray, eq, origin));
}
