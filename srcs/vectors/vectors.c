/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:52:59 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/28 13:53:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/minirt.h"

t_vector	new_vect(float x, float y, float z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

void	normalise_vect(t_vector *vect)
{
	float	len;

	len = vect_len(*vect);
	if (!len)
	{
		vect->x = 0;
		vect->y = 0;
		vect->z = 0;
	}
	else
	{
		vect->x /= len;
		vect->y /= len;
		vect->z /= len;
	}
}

float	vect_dot_product(t_vector v1, t_vector v2)
{
	float	res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

float	point_dist(t_vector v1, t_vector v2)
{
	float	res;

	res = sqrtf((v2.x - v1.x) * (v2.x - v1.x)
			+ (v2.y - v1.y) * (v2.y - v1.y)
			+ (v2.z - v1.z) * (v2.z - v1.z));
	return (res);
}
