/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_preparation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:58:24 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 18:01:47 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/error.h"
#include "../../includes/parsing.h"

void	ft_point_shift(t_vector *point, t_vector *shift)
{
	point->x += -shift->x;
	point->y += -shift->y;
	point->z += -shift->z;
}

void	ft_shift_camera(t_scene *scene)
{
	int	i;

	i = 0;
	while (scene->counter.lights && scene->lights[i])
	{
		ft_point_shift(&scene->lights[i]->point, &scene->camera.point);
		ft_point_shift(&scene->lights[i]->point, &scene->camera.orientation);
		i++;
	}
	i = 0;
	while (scene->objs[i])
	{
		ft_point_shift(&scene->objs[i]->center, &scene->camera.point);
		i++;
	}
	scene->camera.point.x = 0;
	scene->camera.point.y = 0;
	scene->camera.point.z = 0;
}

void	ft_prepare_scene(t_scene *scene)
{
	if (!scene->counter.ambients)
		ft_error(EM_AMBIENT_NDECL, scene);
	if (!scene->counter.cameras)
		ft_error(EM_CAMERA_NDECL, scene);
	if (!scene->counter.lights)
		ft_error(EM_LIGHT_NDECL, scene);
	scene->lights = ft_convert_lights2arr(scene);
	if (!scene->counter.objects)
		ft_error(EM_OBJECT_NDECL, scene);
	scene->objs = ft_convert_objects2arr(scene);
	scene->origin_color = ft_get_rgb(0, 0, 0);
	scene->light = 0;
	scene->object = 0;
	ft_shift_camera(scene);
	ft_camera_rotation(scene);
}
