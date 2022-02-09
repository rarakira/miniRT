/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:52:59 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/09 18:50:56 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mlx.h"
#include "minirt.h"
#include "error_msgs.h"

/*
 * Вычитание векторов
 * a{a1, a2}; b{b1, b2}
 * c = a - b = c{a1-b1, a2-b2}
 */
t_vector	vect_substract(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_vector	vect_add(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vector	vect_mult(t_vector vect, float n)
{
	t_vector	res;

	res.x = vect.x * n;
	res.y = vect.y * n;
	res.z = vect.z * n;
	return (res);
}

t_vector	vect_div(t_vector vect, float n)
{
	t_vector	res;

	res.x = vect.x / n;
	res.y = vect.y / n;
	res.z = vect.z / n;
	return (res);
}

/* Длина вектора */
float	vect_len(t_vector vect)
{
	float	res;

	res = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
	return (res);
}
