/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:43:10 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:47:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "ft_printf.h"

static int	win_close(int keycode, t_minirt *minirt)
{
	if (keycode == 53)
	{
		mlx_destroy_image(minirt->mlx, minirt->img);
		mlx_destroy_window(minirt->mlx, minirt->win);
		free_minirt(minirt);
		ft_printf("You pressed ESC. Exiting program, bye!\n");
		exit (1);
	}
	return (0);
}

static int	win_close_x(t_minirt *minirt)
{
	mlx_destroy_image(minirt->mlx, minirt->img);
	mlx_destroy_window(minirt->mlx, minirt->win);
	free_minirt(minirt);
	ft_printf("You clicked [x] button. Exiting program, bye!\n");
	exit (1);
	return (0);
}

static int	mouse_hook(int button, int x, int y, t_minirt *minirt)
{
	(void) minirt;
	ft_printf("Mouse (button = %d) pressed - (%d, %d) !\n", button, x, y);
	return (1);
}

void	register_hooks(t_minirt *minirt)
{
	mlx_key_hook(minirt->win, key_hook, minirt);
	mlx_hook(minirt->win, 2, 1L << 0, win_close, minirt);
	mlx_hook(minirt->win, 17, 1L << 17, win_close_x, minirt);
	mlx_mouse_hook(minirt->win, mouse_hook, minirt);
}
