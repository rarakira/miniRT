/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:02:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 17:24:30 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "minirt.h"
#include "camera.h"
#include "objects.h"

static float	plane_intersects(t_scene *scene, t_object *obj, t_vector *ray)
{
	(void) scene;
	(void) obj;
	(void) ray;
	return (0);
}

static float	cyllinder_intersects(t_scene *scene, t_object *obj, t_vector *ray)
{
	(void) scene;
	(void) obj;
	(void) ray;
	return (0);
}

static float	sphere_intersects(t_scene *scene, t_object *obj, t_vector *ray)
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
	dist_2 = ((b * (-1)) + (sqrt(discr) / 2));
	if (dist_1 > 0)
		return (dist_1);
	else if (dist_2 > 0) // check later
		return (dist_2);
	return (0);
}

int	object_intersects(t_minirt *minirt, t_object **objs, t_vector *ray)
{
	int			i;
	float		res1;
	float		res2[2];

	i = 0;
	res2[0] = -1;
	res2[1] = -1;
	while (objs[i] != NULL)
	{
		if (objs[i]->type == 'S')
			res1 = sphere_intersects(minirt->scene, objs[i], ray);
		else if (objs[i]->type == 'C')
			res1 = cyllinder_intersects(minirt->scene, objs[i], ray);
		else if (objs[i]->type == 'P')
			res1 = plane_intersects(minirt->scene, objs[i], ray);
		if (res1 != 0 && (res2[1] == -1 || res1 < res2[1]))
		{
			res2[0] = i;
			res2[1] = res1;
		}
		i++;
	}
	return (res2[0]);
}
