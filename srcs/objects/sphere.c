/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:56 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 20:50:14 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "../../includes/parsing.h"

static inline float	find_dists(t_camera *cam, t_object *obj, t_vector *ray, t_eq eq)
{
	(void) cam;
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.dist1 = (-eq.b - sqrt(eq.discr)) / (2 * eq.a);
	eq.dist2 = (-eq.b + sqrt(eq.discr)) / (2 * eq.a);
	if (eq.dist1 > MIN_DIST || eq.dist2 > MIN_DIST)
	{
		if (eq.dist1 > MIN_DIST && eq.dist2 > MIN_DIST)
			obj->dist = fmin(eq.dist1, eq.dist2);
		else if (eq.dist1 > MIN_DIST)
			obj->dist = eq.dist1;
		else
			obj->dist = eq.dist2;
		obj->hit_point = vect_mult(ray, obj->dist);
		// obj->hit_point = vect_add(cam->origin, &obj->hit_point);
		obj->hit_norm_v = vect_substract(&obj->hit_point, obj->center);
		normalise_vect(&obj->hit_norm_v);
		return (obj->dist);
	}
	return (0);
}

float	sphere_intersects(t_camera *cam, t_object *obj, t_vector *ray)
{
	t_vector	cam_sp;
	t_eq		eq;

	cam_sp = vect_substract(cam->origin, obj->center);
	eq.a = 1;
	eq.b = 2 * (vect_dot_product(&cam_sp, ray));
	eq.c = vect_dot_product(&cam_sp, &cam_sp) - obj->radius * obj->radius;
	return (find_dists(cam, obj, ray, eq));
}

//t_object	*new_sphere(t_vector *center, float radius, int colour)
//{
//	t_object	*sphere;
//
//	sphere = malloc(sizeof(t_object));
//	if (sphere == NULL)
//		exit_on_error(-1, ERR_MALLOC);
//	ft_memset(sphere, 0, sizeof(t_object));
//	sphere->center = center;
//	sphere->radius = radius;
//	sphere->type = 'S';
//	sphere->colour = colour;
//	sphere->next = 0;
//	sphere->previous = 0;
//	return (sphere);
//}

void	ft_read_sphere(t_minirt *minirt, char *line)
{
	int	i;

	i = 2;
	minirt->objs_lst->type = 'S';
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->center->x = ft_atof(line, &i);
	minirt->objs_lst->center->y = ft_atof(line, &i);
	minirt->objs_lst->center->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->radius = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.b = ft_atoi(&line[++i]);
	minirt->objs_lst->colour = ft_rgb_hex(0, minirt->objs_lst->rgb);
}
