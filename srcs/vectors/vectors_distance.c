/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_dist.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:52:59 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/14 17:03:14 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mlx.h"
#include "minirt.h"
#include "error_msgs.h"


float	point_dist(t_vector v1, t_vector v2)
{
	float	res;

	res = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
	return (res);
}

float	vect_dist(t_vector v1, t_vector v2)
{
	float	res;

	res = (v1.x - v2.x) * (v1.x - v2.x)
		+ (v1.y - v2.y) * (v1.y - v2.y)
		+ (v1.z - v2.z) * (v1.z - v2.z);
	return (res);
}