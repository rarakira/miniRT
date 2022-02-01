/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/01 13:13:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "../../includes/minirt.h"
#include "../../includes/objects.h"

int	object_intersects(t_minirt *minirt, t_object **objs, t_vector *ray)
{
	int			i;
	float		res1;
	float		res2[2];

	i = 0;
	res2[0] = -1;
	res2[1] = MAX_DIST;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res1 = sphere_intersects(minirt->camera, objs[i], ray);
		else if (objs[i]->type == 'C')
			res1 = cylinder_intersects(minirt->camera, objs[i], ray);
		else if (objs[i]->type == 'P')
			res1 = plane_intersects(minirt->camera, objs[i], ray);
		if (res1 != 0 && res1 < res2[1])
		{
			res2[0] = i;
			res2[1] = res1;
		}
		i++;
	}
	return (res2[0]);
}
