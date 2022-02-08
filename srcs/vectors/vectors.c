/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:52:59 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 16:05:10 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

//#include "../../libs/minilibx_macos/mlx.h"
#include "../../includes/minirt.h"
#include "../../includes/error_msgs.h"

t_vector	*new_vect(float x, float y, float z)
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (new == NULL)
		exit_on_error(-1, ERR_MALLOC);
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

/*
 * Нормализация вектора — преобразование заданного вектора в вектор в том
 * же направлении (то есть в коллинеарный, параллельный вектор), но с
 * единичной длиной.
 */
void	normalise_vect(t_vector *vect)
{
	float	len;

	len = vect_len(vect);
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

/*
 * Скалярное произведение векторов в ДЕКАРТОВЫХ КООРДИНАТАХ (частный случай)
 * вектор a {xa, ya, za}; вектор b {xb, yb, zb}
 * скалярное произведение векторов a*b = xa*xb + ya*yb + za*zb
 * доказательство через разложение по бозису ijk
 * a*b = (xa*i + ya*j + za*k) * (xb*i + yb*j + zb*k) =
 * = xa*xb*pow(i) + xa*yb*cos(90) + xa*zb*cos(90) + ...
 * cos(90) = 0, i = j = k = 1 ->
 * a*b = xa*xb + ya*yb + za*zb
 */
float	vect_dot_product(t_vector *v1, t_vector *v2)
{
	float	res;

	res = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (res);
}

float	vector_scalar(t_vector v1, t_vector v2)
{
	float	res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (res);
}

t_vector	reflect_vector(t_vector ray, t_vector norm)
{
	t_vector	res;

	res = vect_mult(&norm, 2);
	res = vect_mult(&res, vector_scalar(norm, ray));
	res = vect_substract(&res, &ray);
	return (res);
}
