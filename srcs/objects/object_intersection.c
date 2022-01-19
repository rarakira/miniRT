/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 15:49:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "minirt.h"
#include "camera.h"
#include "objects.h"

static int	sphere_intersects(t_scene *scene, t_object *obj, t_vector *ray)
{
	float		b;
	float		c;
	float		discr;
	float		dist_1;
	float		dist_2;
	t_vector	*cam_sp;

	dist_1 = 0;
	dist_2 = 0;
	cam_sp = vect_substract(scene->cams->origin, obj->center);
	b = 2 * (vect_dot_product(cam_sp, ray));
	c = vect_dot_product(cam_sp, cam_sp) - pow(obj->radius, 2);
	discr = pow(b, 2) - (4 * c);
	free(cam_sp);
	if (discr < 0)
		return (0);
	dist_1 = ((b * (-1)) - (sqrt(discr) / 2));
	dist_2 = ((b * (-1)) + (sqrt(discr) / 2)); // for later
	return (dist_1 > 0);
}

int	object_intersects(t_minirt *minirt, t_object **objs, t_vector *ray)
{
	int		i;

	i = 0;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S' && sphere_intersects(minirt->scene, objs[i], ray))
			return (i);
		i++;
	}
	return (-1);
}
