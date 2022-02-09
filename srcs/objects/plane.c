/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:15 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/09 19:38:30 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/parsing.h"

float	plane_intersects(t_vector origin, t_object *obj, t_vector ray)
{
	float		dot_r_nv;
	t_vector	orig_pl;

	normalise_vect(obj->norm_v);
	dot_r_nv = vect_dot_product(ray, *obj->norm_v);
	if (dot_r_nv == 0 || fabs(dot_r_nv) < MIN_DIST)
		return (0);
	orig_pl = vect_substract(origin, *obj->center);
	obj->dist = -vect_dot_product(orig_pl, *obj->norm_v) / dot_r_nv;
	if (obj->dist < MIN_DIST || obj->dist > MAX_DIST)
		return (0);
	obj->hit_point = vect_mult(ray, obj->dist);
	obj->hit_norm_v = *obj->norm_v;
	if (dot_r_nv < 0.0)
		obj->hit_norm_v = vect_mult(obj->hit_norm_v, -1);
	normalise_vect(&obj->hit_norm_v);
	return (obj->dist);
}

void	ft_read_plane(t_minirt *minirt, char *line)
{
	int	i;

	i = 2;
	minirt->objs_lst->type = 'P';
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
	minirt->objs_lst->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.b = ft_atoi(&line[++i]);
	minirt->objs_lst->colour = ft_rgb_hex(0, minirt->objs_lst->rgb);
}
