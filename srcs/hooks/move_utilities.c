/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:50:00 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 13:12:10 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

void	ft_axis_move_x(t_minirt *minirt, char sign)
{
	int	i;

	i = 0;
	while (minirt->scene.objs[i])
	{
		minirt->scene.objs[i]->center.x += 1 * sign;
		i++;
	}
	i = 0;
	while (minirt->scene.lights[i])
	{
		minirt->scene.lights[i]->point.x += 1 * sign;
		i++;
	}
}

void	ft_axis_move_y(t_minirt *minirt, char sign)
{
	int	i;

	i = 0;
	while (minirt->scene.objs[i])
	{
		minirt->scene.objs[i]->center.y += 1 * sign;
		i++;
	}
	i = 0;
	while (minirt->scene.lights[i])
	{
		minirt->scene.lights[i]->point.y += 1 * sign;
		i++;
	}
}

void	ft_axis_move_z(t_minirt *minirt, char sign)
{
	int	i;

	i = 0;
	while (minirt->scene.objs[i])
	{
		minirt->scene.objs[i]->center.z += 1 * sign;
		i++;
	}
	i = 0;
	while (minirt->scene.lights[i])
	{
		minirt->scene.lights[i]->point.z += 1 * sign;
		i++;
	}
}
