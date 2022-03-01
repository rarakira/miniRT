/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:52:04 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/28 12:09:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

int	ft_exit_hook(int keycode, t_minirt *minirt)
{
	if (keycode == 53)
	{
		ft_free_scene(&minirt->scene);
		mlx_destroy_image(minirt->mlx, minirt->img);
		mlx_clear_window(minirt->mlx, minirt->win);
		mlx_destroy_window(minirt->mlx, minirt->win);
		printf("You pressed [ESC] button.\n"
			TC_OK"Exiting program!\n\n"TC_END);
		exit(0);
	}
	return (0);
}

int	ft_red_cross_hook(t_minirt *minirt)
{
	ft_free_scene(&minirt->scene);
	mlx_destroy_image(minirt->mlx, minirt->img);
	mlx_clear_window(minirt->mlx, minirt->win);
	mlx_destroy_window(minirt->mlx, minirt->win);
	printf("You clicked on the red cross on the window’s frame.\n"
		TC_OK"Exiting program!\n\n"TC_END);
	exit(0);
}
