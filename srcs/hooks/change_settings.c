/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_settings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:24:15 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 14:39:32 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_change_radius(t_minirt *minirt, char sign)
{
	if (minirt->scene.object && minirt->scene.object->type != 'L'
		&& ((minirt->scene.object->radius > 0.1 && sign < 0) || sign > 0))
		minirt->scene.object->radius += 0.05 * sign;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_change_height(t_minirt *minirt, char sign)
{
	if (minirt->scene.object
		&& ((minirt->scene.object->height > 0.1 && sign < 0) || sign > 0))
		minirt->scene.object->height += 0.1 * sign;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}

void	ft_change_brightness(t_minirt *minirt, char sign)
{
	if (minirt->scene.light
		&& ((minirt->scene.light->brightness > 0 && sign < 0)
			|| (minirt->scene.light->brightness < 1 && sign > 0)))
			minirt->scene.light->brightness += 0.1 * sign;
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
}
