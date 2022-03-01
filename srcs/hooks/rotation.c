/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:18:24 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 13:28:21 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_x_rotation(t_minirt *minirt, char direction)
{
	float	cos_a;
	float	sin_a;

	ft_get_sin_a_cos(&cos_a, &sin_a, direction);
	if (!minirt->scene.object)
	{
		ft_objs_x_axis_rotation(minirt->scene.objs, cos_a, sin_a);
		ft_lights_x_axis_rotation(minirt->scene.lights, cos_a, sin_a);
	}
	else if (minirt->scene.object->norm_v.x || minirt->scene.object->norm_v.z)
	{
		minirt->scene.object->norm_v.x = minirt->scene.object->norm_v.x * cos_a
			- minirt->scene.object->norm_v.z * sin_a;
		minirt->scene.object->norm_v.z = minirt->scene.object->norm_v.x * sin_a
			+ minirt->scene.object->norm_v.z * cos_a;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_y_rotation(t_minirt *minirt, char direction)
{
	float	cos_a;
	float	sin_a;

	ft_get_sin_a_cos(&cos_a, &sin_a, direction);
	if (!minirt->scene.object)
	{
		ft_objs_y_axis_rotation(minirt->scene.objs, cos_a, sin_a);
		ft_lights_y_axis_rotation(minirt->scene.lights, cos_a, sin_a);
	}
	else if (minirt->scene.object->norm_v.y || minirt->scene.object->norm_v.z)
	{
		minirt->scene.object->norm_v.y = minirt->scene.object->norm_v.y * cos_a
			- minirt->scene.object->norm_v.z * sin_a;
		minirt->scene.object->norm_v.z = minirt->scene.object->norm_v.y * sin_a
			+ minirt->scene.object->norm_v.z * cos_a;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
