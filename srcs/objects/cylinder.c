/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/09 11:56:51 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/parsing.h"

static inline float	find_dists_cy(	t_object *obj,
									t_vector *orig_cyl, t_vector *ray, t_eq eq)
{
	short		is_valid1;
	short		is_valid2;
	t_vector	tmp;

	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.dist1 = (-eq.b - sqrt(eq.discr)) / (2 * eq.a);
	eq.dist2 = (-eq.b + sqrt(eq.discr)) / (2 * eq.a);
	eq.m1 = vect_dot_product(ray, obj->norm_v) * eq.dist1
		+ vect_dot_product(orig_cyl, obj->norm_v);
	eq.m2 = vect_dot_product(ray, obj->norm_v) * eq.dist2
		+ vect_dot_product(orig_cyl, obj->norm_v);
	is_valid1 = (eq.dist1 > MIN_DIST
			&& eq.m1 >= -obj->height && eq.m1 <= obj->height);
	is_valid2 = (eq.dist2 > MIN_DIST
			&& eq.m2 >= -obj->height && eq.m2 <= obj->height);
	if (is_valid1 || is_valid2)
	{
		if (is_valid1 && is_valid2 && eq.dist1 > eq.dist2)
			obj->dist = eq.dist2;
		else if (is_valid1)
			obj->dist = eq.dist1;
		else
			obj->dist = eq.dist2;
		obj->m = eq.m1;
		if (obj->dist == eq.dist2)
			obj->m = eq.m2;
		obj->hit_point = vect_mult(ray, obj->dist);
		obj->hit_norm_v = vect_substract(&obj->hit_point, obj->center);
		tmp = vect_mult(obj->norm_v, obj->m);
		obj->hit_norm_v = vect_substract(&obj->hit_norm_v, &tmp);
		normalise_vect(&obj->hit_norm_v);
		return (obj->dist);
	}
	return (0);
}

float	cylinder_intersects(t_vector *origin, t_object *obj, t_vector *ray)
{
	t_vector	orig_cyl;
	t_eq		eq;
	float		dot_r_nv;
	float		dot_cc_nv;

	orig_cyl = vect_substract(origin, obj->center);
	normalise_vect(obj->norm_v);
	dot_r_nv = vect_dot_product(ray, obj->norm_v);
	dot_cc_nv = vect_dot_product(&orig_cyl, obj->norm_v);
	eq.a = vect_dot_product(ray, ray)
		- dot_r_nv * dot_r_nv;
	eq.b = 2 * (vect_dot_product(ray, &orig_cyl) - dot_r_nv * dot_cc_nv);
	eq.c = vect_dot_product(&orig_cyl, &orig_cyl)
		- dot_cc_nv * dot_cc_nv - obj->radius * obj->radius;
	return (find_dists_cy(obj, &orig_cyl, ray, eq));
}

void	ft_read_cylinder(t_minirt *minirt, char *line)
{
	int	i;

	i = 2;
	minirt->objs_lst->type = 'C';
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->center->x = ft_atof(line, &i);
	minirt->objs_lst->center->y = ft_atof(line, &i);
	minirt->objs_lst->center->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->norm_v->x = ft_atof(line, &i);
	minirt->objs_lst->norm_v->y = ft_atof(line, &i);
	minirt->objs_lst->norm_v->z = ft_atof(line, &i);
	normalise_vect(minirt->objs_lst->norm_v);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->radius = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->height = ft_atof(line, &i) / 2;
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
