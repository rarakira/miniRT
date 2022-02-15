/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/15 15:04:43 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "minirt.h"
#include "objects.h"
#include "../../includes/parsing.h"

static int	in_range(float num, float range)
{
	if (num < -range)
		return (0);
	if (num > range)
		return (0);
	return (1);
}

static void	update_hit_point(t_intersection *hit, float dist, float m)
{
	hit->dist = dist;
	hit->m = m;
}

static float	get_dist(t_object *obj, t_vector ray, t_eq body)
{
	t_eq	caps;

	ft_memset(&caps, 0, sizeof(t_eq));
	obj->hit.type = BODY;
	if (in_range(body.m1, obj->height) && in_range(body.m2, obj->height))
	{
		update_hit_point(&obj->hit, body.dist1, body.m1);
		if (body.dist1 > body.dist2)
			update_hit_point(&obj->hit, body.dist2, body.m2);
	}
	else
	{
		if (!get_cylinder_caps(&caps, obj, ray) && !in_range(body.m1, obj->height) && !in_range(body.m2, obj->height))
			return (0);
		if (in_range(body.m1, obj->height) && (body.dist1 < caps.dist1 || caps.dist1 < MIN_DIST))
			update_hit_point(&obj->hit, body.dist1, body.m1);
		else if (in_range(body.m2, obj->height) &&  (body.dist2 < caps.dist1 || caps.dist1 < MIN_DIST))
			update_hit_point(&obj->hit, body.dist2, body.m2);
		else
		{
			obj->hit.type = CAP;
			update_hit_point(&obj->hit, caps.dist1, caps.m1);
		}
	}
	return (obj->hit.dist);
}

static inline float	find_dists_cy(	t_object *obj,
									t_vector orig_cyl, t_vector ray, t_eq eq)
{
	eq.discr = eq.b * eq.b - (4 * eq.a * eq.c);
	if (eq.discr < 0.0)
		return (0);
	eq.discr = sqrt(eq.discr);
	eq.dist1 = (-eq.b - eq.discr) / (2 * eq.a);
	eq.dist2 = (-eq.b + eq.discr) / (2 * eq.a);
	eq.m1 = vect_dot_product(ray, *obj->norm_v) * eq.dist1
		+ vect_dot_product(orig_cyl, *obj->norm_v);
	eq.m2 = vect_dot_product(ray, *obj->norm_v) * eq.dist2
		+ vect_dot_product(orig_cyl, *obj->norm_v);
	if (eq.dist1 <= MIN_DIST)
		eq.m1 = obj->height + 1.0;
	if (eq.dist2 <= MIN_DIST)
		eq.m2 = obj->height + 1.0;
	return (get_dist(obj, ray, eq));
}

float	cylinder_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	t_vector	orig_cyl;
	t_eq		eq;
	float		dot_r_nv;
	float		dot_cc_nv;

	orig_cyl = vect_substract(origin, *obj->center);
	normalise_vect(obj->norm_v);
	dot_r_nv = vect_dot_product(ray, *obj->norm_v);
	dot_cc_nv = vect_dot_product(orig_cyl, *obj->norm_v);
	eq.a = vect_dot_product(ray, ray)
		- dot_r_nv * dot_r_nv;
	eq.b = 2 * (vect_dot_product(ray, orig_cyl) - dot_r_nv * dot_cc_nv);
	eq.c = vect_dot_product(orig_cyl, orig_cyl)
		- dot_cc_nv * dot_cc_nv - obj->radius * obj->radius;
	return (find_dists_cy(obj, orig_cyl, ray, eq));
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
