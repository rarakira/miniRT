/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_utilities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 13:20:36 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 13:25:14 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_get_sin_a_cos(float *cos_a, float *sin_a, char direction)
{
	float	angle_a;

	if (direction > 0)
		angle_a = -0.1;
	else if (direction < 0)
		angle_a = 0.1;
	else
		angle_a = 0;
	*cos_a = cosf(angle_a);
	*sin_a = sinf(angle_a);
}

void	ft_objs_x_axis_rotation(t_object **objs, float cos_a, float sin_a)
{
	int		i;
	float	rx;
	float	rz;

	i = 0;
	while (objs[i])
	{
		rx = objs[i]->center.x * cos_a - objs[i]->center.z * sin_a;
		rz = objs[i]->center.x * sin_a + objs[i]->center.z * cos_a;
		objs[i]->center.x = rx;
		objs[i]->center.z = rz;
		if (objs[i]->norm_v.x || objs[i]->norm_v.y || objs[i]->norm_v.z)
		{
			rx = objs[i]->norm_v.x * cos_a - objs[i]->norm_v.z * sin_a;
			rz = objs[i]->norm_v.x * sin_a + objs[i]->norm_v.z * cos_a;
			objs[i]->norm_v.x = rx;
			objs[i]->norm_v.z = rz;
		}
		i++;
	}
}

void	ft_lights_x_axis_rotation(t_light **lights, float cos_a, float sin_a)
{
	int		i;
	float	rx;
	float	rz;

	i = 0;
	while (lights[i])
	{
		rx = lights[i]->point.x * cos_a - lights[i]->point.z * sin_a;
		rz = lights[i]->point.x * sin_a + lights[i]->point.z * cos_a;
		lights[i]->point.x = rx;
		lights[i]->point.z = rz;
		i++;
	}
}

void	ft_objs_y_axis_rotation(t_object **objs, float cos_a, float sin_a)
{
	int		i;
	float	ry;
	float	rz;

	i = 0;
	while (objs[i])
	{
		ry = objs[i]->center.y * cos_a - objs[i]->center.z * sin_a;
		rz = objs[i]->center.y * sin_a + objs[i]->center.z * cos_a;
		objs[i]->center.y = ry;
		objs[i]->center.z = rz;
		if (objs[i]->norm_v.x || objs[i]->norm_v.y || objs[i]->norm_v.z)
		{
			ry = objs[i]->norm_v.y * cos_a - objs[i]->norm_v.z * sin_a;
			rz = objs[i]->norm_v.y * sin_a + objs[i]->norm_v.z * cos_a;
			objs[i]->norm_v.y = ry;
			objs[i]->norm_v.z = rz;
		}
		i++;
	}
}

void	ft_lights_y_axis_rotation(t_light **lights, float cos_a, float sin_a)
{
	int		i;
	float	ry;
	float	rz;

	i = 0;
	while (lights[i])
	{
		ry = lights[i]->point.y * cos_a - lights[i]->point.z * sin_a;
		rz = lights[i]->point.y * sin_a + lights[i]->point.z * cos_a;
		lights[i]->point.y = ry;
		lights[i]->point.z = rz;
		i++;
	}
}
