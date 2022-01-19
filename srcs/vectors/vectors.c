/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:52:59 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:46:10 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "mlx.h"
#include "minirt.h"
#include "error_msgs.h"

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

t_vector	*vect_substract(t_vector *v1, t_vector *v2)
{
	t_vector	*res;

	res = new_vect(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (res);
}

float	vect_len(t_vector *vect)
{
	float	res;

	res = sqrt(pow(vect->x, 2) + pow(vect->y, 2) + pow(vect->z, 2));
	return (res);
}

/* REPLACE ??? vect->x *= pow(len, -1) */
void	normalise_vect(t_vector *vect)
{
	float	len;

	len = vect_len(vect);
	vect->x /= len;
	vect->y /= len;
	vect->z /= len;
}

float	vect_dot_product(t_vector *v1, t_vector *v2)
{
	float	res;

	res = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (res);
}
