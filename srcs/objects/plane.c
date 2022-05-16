/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:15 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 20:58:31 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/minirt.h"

float	plane_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	float		dot_r_nv;
	t_vector	orig_pl;

	obj->hit.is_inside = 0;
	normalise_vect(&obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	orig_pl = vect_substract(origin, obj->center);
	obj->hit.dist = -vect_dot_product(orig_pl, obj->norm_v) / dot_r_nv;
	if (obj->hit.dist < MIN_DIST || obj->hit.dist > MAX_DIST)
		return (0);
	return (obj->hit.dist);
}
