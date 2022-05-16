/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:24:51 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 21:29:56 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/structure_prototypes.h"
#include "../../includes/minirt.h"

t_rgb	ft_checkerboard(t_object *sphere, t_point *point)
{
	double		v;
	double		u;
	double		theta;
	double		phi;
	t_vector	upd_point;

	upd_point = vect_substract(point->hit_coord, sphere->center);
	theta = atan2(upd_point.x, upd_point.z);
	phi = acos(upd_point.y / sphere->radius);
	u = theta / (2 * M_PI);
	u = floor(10 * (1 - (u + 0.5)));
	v = floor(10 * (1 - (phi / M_PI)) / 2);
	if (fmod(u + v, 2) == 0)
		return (invert_color(sphere->rgb));
	else
		return (sphere->rgb);
}
