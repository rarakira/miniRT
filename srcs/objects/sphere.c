/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:56 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/15 14:06:36 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "../../includes/parsing.h"

static inline float	find_dists(t_object *obj, t_vector ray, t_eq eq)
{
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.discr = sqrt(eq.discr);
	eq.dist1 = (-eq.b - eq.discr) / (2 * eq.a);
	eq.dist2 = (-eq.b + eq.discr) / (2 * eq.a);
	obj->hit.is_inside = 1;
	if (eq.dist1 > MIN_DIST || eq.dist2 > MIN_DIST)
	{
		if (eq.dist1 > MIN_DIST && eq.dist2 > MIN_DIST)
		{
			obj->hit.dist = fmin(eq.dist1, eq.dist2);
			obj->hit.is_inside = 0;
		}
		else if (eq.dist1 > MIN_DIST)
			obj->hit.dist = eq.dist1;
		else
			obj->hit.dist = eq.dist2;
		obj->hit.point = vect_mult(ray, obj->hit.dist);
		return (obj->hit.dist);
	}
	return (0);
}

float	sphere_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	t_vector	orig_sp;
	t_eq		eq;

	orig_sp = vect_substract(origin, *obj->center);
	eq.a = 1;
	eq.b = 2 * (vect_dot_product(orig_sp, ray));
	eq.c = vect_dot_product(orig_sp, orig_sp) - obj->radius * obj->radius;
	return (find_dists(obj, ray, eq));
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
