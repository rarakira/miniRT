/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:13:01 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/01 13:13:48 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "../../includes/parsing.h"

static inline float	find_dists_cy(t_object *obj, t_vector *cam_cyl, t_vector *ray)
{
	float	m1;
	float	m2;

	obj->discr = pow(obj->b, 2) - (4 * obj->a * obj->c);
	if (obj->discr < 0.0)
		return (0);
	obj->dist1 = (-obj->b - sqrt(obj->discr)) / (2 * obj->a);
	obj->dist2 = (-obj->b + sqrt(obj->discr)) / (2 * obj->a);
	m1 = vect_dot_product(ray, obj->norm_v) * obj->dist1
		+ vect_dot_product(cam_cyl, obj->norm_v);
	m2 = vect_dot_product(ray, obj->norm_v) * obj->dist2
		+ vect_dot_product(cam_cyl, obj->norm_v);
	free(cam_cyl);
	if ((obj->dist1 > MIN_DIST && m1 >= -obj->height && m1 <= obj->height)
		&& (obj->dist2 > MIN_DIST && m2 >= -obj->height && m2 <= obj->height))
		return (fmin(obj->dist1, obj->dist2));
	else if (obj->dist1 > MIN_DIST && m1 >= -obj->height && m1 <= obj->height)
		return (obj->dist1);
	else if (obj->dist2 > MIN_DIST && m2 >= -obj->height && m2 <= obj->height)
		return (obj->dist2);
	return (0);
}

float	cylinder_intersects(t_camera *cam, t_object *obj, t_vector *ray)
{
	t_vector	*cam_cyl;

	cam_cyl = vect_substract(cam->origin, obj->center);
	normalise_vect(obj->norm_v);
	obj->a = vect_dot_product(ray, ray)
		- pow(vect_dot_product(ray, obj->norm_v), 2);
	obj->b = 2 * (vect_dot_product(ray, cam_cyl)
			- vect_dot_product(ray, obj->norm_v)
			* vect_dot_product(cam_cyl, obj->norm_v));
	obj->c = vect_dot_product(cam_cyl, cam_cyl)
		- pow(vect_dot_product(cam_cyl, obj->norm_v), 2) - pow(obj->radius, 2);
	return (find_dists_cy(obj, cam_cyl, ray));
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
