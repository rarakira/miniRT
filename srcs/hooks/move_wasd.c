/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_wasd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:23:04 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 13:10:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_w_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_z(minirt, 1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.z -= 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.z -= 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_a_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_x(minirt, 1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.x -= 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.x -= 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_s_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_z(minirt, -1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.z += 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.z += 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_d_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_x(minirt, -1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.x += 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.x += 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
