/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:10:18 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 15:10:18 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_apply_texture(t_minirt *minirt)
{
	if (minirt->apply_texture)
		minirt->apply_texture = 0;
	else
		minirt->apply_texture = 1;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_apply_bump(t_minirt *minirt)
{
	if (minirt->apply_bump)
		minirt->apply_bump = 0;
	else
		minirt->apply_bump = 1;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_apply_checkerboard(t_minirt *minirt)
{
	if (minirt->apply_checkerboard)
		minirt->apply_checkerboard = 0;
	else
		minirt->apply_checkerboard = 1;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
