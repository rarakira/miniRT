/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:15 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/01 14:28:36 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/parsing.h"

float	plane_intersects(t_camera *cam, t_object *obj, t_vector *ray)
{
	float		r_nv;
	t_vector	cam_pl;

	normalise_vect(obj->norm_v);
	r_nv = vect_dot_product(ray, obj->norm_v);
	if (r_nv == 0 || fabs(r_nv) < MIN_DIST)
		return (0);
	cam_pl = vect_substract(cam->origin, obj->center);
	obj->dist1 = -1 * vect_dot_product(&cam_pl, obj->norm_v) / r_nv;
	if (obj->dist1 < MIN_DIST || obj->dist1 > MAX_DIST)
		return (0);
	return (obj->dist1);
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
