/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:05:36 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/02 12:52:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_get_camera_sin_a_cos(float *cos_a, float *sin_a, float angle_a,
								char direction)
{
	*cos_a = cosf(angle_a * direction);
	*sin_a = sinf(angle_a * direction);
}

void	ft_camera_rotation(t_scene *scene)
{
	ft_x_camera_rotation(scene);
	ft_y_camera_rotation(scene);
	ft_z_camera_rotation(scene);
}
