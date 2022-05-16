/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_objects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:01:54 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/02 12:05:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/error.h"
#include "../../includes/parsing.h"

void	ft_parsing_sphere(t_scene *scene, char *str, int i)
{
	scene->object->type = SPHERE;
	scene->object->center = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->object->norm_v.x = 0;
	scene->object->norm_v.y = 1;
	scene->object->norm_v.z = 0;
	scene->object->radius = ft_atof(str, &i) / 2;
	ft_check_next_parametr(str, i, scene);
	scene->object->rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->object->rgb))
		ft_error(EM_SPHERE_COLOR, scene);
	scene->counter.objects++;
}

void	ft_parsing_plane(t_scene *scene, char *str, int i)
{
	scene->object->type = PLANE;
	scene->object->center = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->object->norm_v = ft_parsing_vector(str, &i, scene);
	if (ft_check_orientation(scene->object->norm_v))
		ft_error(EM_PLANE_ORIENT, scene);
	if (vect_len(scene->object->norm_v) != 1)
		ft_normal_error(EM_PLANE_NNORM, &scene->object->norm_v);
	ft_check_next_parametr(str, i, scene);
	scene->object->rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->object->rgb))
		ft_error(EM_PLANE_COLOR, scene);
	scene->counter.objects++;
}

void	ft_parsing_cylinder(t_scene *scene, char *str, int i)
{
	scene->object->type = CYLINDER;
	scene->object->center = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->object->norm_v = ft_parsing_vector(str, &i, scene);
	if (ft_check_orientation(scene->object->norm_v))
		ft_error(EM_CLND_ORIENT, scene);
	if (vect_len(scene->object->norm_v) != 1)
		ft_normal_error(EM_CLND_NNORM, &scene->object->norm_v);
	ft_check_next_parametr(str, i, scene);
	scene->object->radius = ft_atof(str, &i) / 2;
	ft_check_next_parametr(str, i, scene);
	scene->object->height = ft_atof(str, &i) / 2;
	ft_check_next_parametr(str, i, scene);
	scene->object->rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->object->rgb))
		ft_error(EM_CLND_COLOR, scene);
	scene->counter.objects++;
}

void	ft_parsing_cone(t_scene *scene, char *str, int i)
{
	scene->object->type = CONE;
	scene->object->center = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->object->norm_v = ft_parsing_vector(str, &i, scene);
	if (ft_check_orientation(scene->object->norm_v))
		ft_error(EM_CONE_ORIENT, scene);
	if (vect_len(scene->object->norm_v) != 1)
		ft_normal_error(EM_CONE_NNORM, &scene->object->norm_v);
	ft_check_next_parametr(str, i, scene);
	scene->object->radius = ft_atof(str, &i) / 2;
	ft_check_next_parametr(str, i, scene);
	scene->object->height = ft_atof(str, &i);
	ft_check_next_parametr(str, i, scene);
	scene->object->rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->object->rgb))
		ft_error(EM_CONE_COLOR, scene);
	scene->counter.objects++;
}
