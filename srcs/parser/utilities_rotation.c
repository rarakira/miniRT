/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_rotation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:11:43 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/02 18:21:51 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_get_camera_sin_a_cos(float *cos_a, float *sin_a, float angle_a,
			char direction);

void	ft_x_camera_rotation(t_scene *scene)
{
	float	cos_a;
	float	sin_a;

	cos_a = 0;
	if (scene->camera.orientation.x == 1)
		sin_a = -1;
	else if (scene->camera.orientation.x == -1)
		sin_a = 1;
	else
		ft_get_camera_sin_a_cos(&cos_a, &sin_a,
			scene->camera.orientation.x, -1);
	ft_objs_x_axis_rotation(scene->objs, cos_a, sin_a);
	ft_lights_x_axis_rotation(scene->lights, cos_a, sin_a);
	scene->camera.orientation.x = 0;
}

void	ft_y_camera_rotation(t_scene *scene)
{
	float	cos_a;
	float	sin_a;

	cos_a = 0;
	if (scene->camera.orientation.y == 1)
		sin_a = -1;
	else if (scene->camera.orientation.y == -1)
		sin_a = 1;
	else
		ft_get_camera_sin_a_cos(&cos_a, &sin_a,
			scene->camera.orientation.y, -1);
	ft_objs_y_axis_rotation(scene->objs, cos_a, sin_a);
	ft_lights_y_axis_rotation(scene->lights, cos_a, sin_a);
	scene->camera.orientation.y = 0;
}

static void	ft_objs_z_axis_rotation(t_object **objs, float cos_a, float sin_a)
{
	int		i;
	float	rx;
	float	ry;

	i = 0;
	while (objs[i])
	{
		rx = objs[i]->center.x * cos_a - objs[i]->center.y * sin_a;
		ry = objs[i]->center.x * sin_a + objs[i]->center.y * cos_a;
		objs[i]->center.x = rx;
		objs[i]->center.y = ry;
		if (objs[i]->norm_v.x || objs[i]->norm_v.y || objs[i]->norm_v.z)
		{
			rx = objs[i]->norm_v.x * cos_a - objs[i]->norm_v.y * sin_a;
			ry = objs[i]->norm_v.x * sin_a + objs[i]->norm_v.y * cos_a;
			objs[i]->norm_v.x = rx;
			objs[i]->norm_v.y = ry;
		}
		i++;
	}
}

static void	ft_lights_z_axis_rotation(t_light **lights, float cos_a, float
sin_a)
{
	int		i;
	float	rx;
	float	ry;

	i = 0;
	while (lights[i])
	{
		rx = lights[i]->point.x * cos_a - lights[i]->point.y * sin_a;
		ry = lights[i]->point.x * sin_a + lights[i]->point.y * cos_a;
		lights[i]->point.x = rx;
		lights[i]->point.y = ry;
		i++;
	}
}

void	ft_z_camera_rotation(t_scene *scene)
{
	float	cos_a;
	float	sin_a;

	if (scene->camera.orientation.z)
	{
		if (scene->camera.orientation.z > 0)
		{
			sin_a = 0;
			cos_a = -1;
			ft_objs_y_axis_rotation(scene->objs, cos_a, sin_a);
			ft_lights_y_axis_rotation(scene->lights, cos_a, sin_a);
			ft_get_camera_sin_a_cos(&cos_a, &sin_a,
				scene->camera.orientation.z, 1);
		}
		sin_a = 0;
		cos_a = -scene->camera.orientation.z;
		ft_objs_z_axis_rotation(scene->objs, cos_a, sin_a);
		ft_lights_z_axis_rotation(scene->lights, cos_a, sin_a);
	}
	scene->camera.orientation.z = 0;
}
