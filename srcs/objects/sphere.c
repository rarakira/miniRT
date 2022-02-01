/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:56 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/01 13:13:52 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "../../includes/parsing.h"

static inline float	find_dists(t_object *obj)
{
	obj->discr = pow(obj->b, 2) - (4 * obj->a * obj->c);
	if (obj->discr < 0.0)
		return (0);
	obj->dist1 = (-obj->b - sqrt(obj->discr)) / (2 * obj->a);
	obj->dist2 = (-obj->b + sqrt(obj->discr)) / (2 * obj->a);
	if (obj->dist1 > MIN_DIST && obj->dist2 > MIN_DIST)
		return (fmin(obj->dist1, obj->dist2));
	else if (obj->dist1 > MIN_DIST)
		return (obj->dist1);
	else if (obj->dist2 > MIN_DIST)
		return (obj->dist2);
	return (0);
}

float	sphere_intersects(t_camera *cam, t_object *obj, t_vector *ray)
{
	t_vector	*cam_sp;

	cam_sp = vect_substract(cam->origin, obj->center);
	obj->a = 1;
	obj->b = 2 * (vect_dot_product(cam_sp, ray));
	obj->c = vect_dot_product(cam_sp, cam_sp) - pow(obj->radius, 2);
	free(cam_sp);
	return (find_dists(obj));
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
