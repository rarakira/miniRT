/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:56 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/23 11:49:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

#include "../../includes/minirt.h"

static inline float	find_dists(t_object *obj, t_vector ray, t_eq eq)
{
	(void )ray;
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.discr = sqrt(eq.discr);
	eq.dist1 = (-eq.b - eq.discr) / (2 * eq.a);
	eq.dist2 = (-eq.b + eq.discr) / (2 * eq.a);
	obj->hit.is_inside = 1;
	if (eq.dist1 > MIN_DIST || eq.dist2 > MIN_DIST)
	{
		if (eq.dist1 > MIN_DIST && eq.dist2 > MIN_DIST)
		{
			obj->hit.dist = fmin(eq.dist1, eq.dist2);
			obj->hit.is_inside = 0;
		}
		else if (eq.dist1 > MIN_DIST)
			obj->hit.dist = eq.dist1;
		else
			obj->hit.dist = eq.dist2;
		return (obj->hit.dist);
	}
	return (0);
}

float	sphere_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	t_vector	orig_sp;
	t_eq		eq;

	orig_sp = vect_substract(origin, obj->center);
	eq.a = 1;
	eq.b = 2 * (vect_dot_product(orig_sp, ray));
	eq.c = vect_dot_product(orig_sp, orig_sp) - obj->radius * obj->radius;
	return (find_dists(obj, ray, eq));
}
