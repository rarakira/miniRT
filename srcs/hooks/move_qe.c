/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_qe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:27:24 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 13:01:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_q_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_y(minirt, 1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.y += 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.y += 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_e_move(t_minirt *minirt)
{
	if (!minirt->scene.object)
		ft_axis_move_y(minirt, -1);
	else if (minirt->scene.object)
	{
		minirt->scene.object->center.y -= 1;
		if (minirt->scene.object->type == 'L')
			minirt->scene.light->point.y -= 1;
	}
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
