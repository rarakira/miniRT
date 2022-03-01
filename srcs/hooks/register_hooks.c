/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:43:10 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 18:20:17 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hooks.h"

static int	fl_select_object(int button, int x, int y, t_minirt *minirt)
{
	(void) minirt;
	if (button == 1
		&& (x >= 0 && x <= WIN_WIDTH)
		&& (y >= 0 && y <= WIN_HEIGHT))
		ft_object_selection(x, y, minirt);
	return (0);
}

static void	ft_orientation_hook(int keycode, t_minirt *minirt)
{
	if (keycode == 12)
		ft_q_move(minirt);
	else if (keycode == 13)
		ft_w_move(minirt);
	else if (keycode == 14)
		ft_e_move(minirt);
	else if (keycode == 0)
		ft_a_move(minirt);
	else if (keycode == 1)
		ft_s_move(minirt);
	else if (keycode == 2)
		ft_d_move(minirt);
	else if (keycode == 123)
		ft_x_rotation(minirt, -1);
	else if (keycode == 124)
		ft_x_rotation(minirt, 1);
	else if (keycode == 125)
		ft_y_rotation(minirt, -1);
	else if (keycode == 126)
		ft_y_rotation(minirt, 1);
}

static void	ft_manipulation_hook(int keycode, t_minirt *minirt)
{
	if (keycode == 18)
		ft_change_radius(minirt, -1);
	else if (keycode == 19)
		ft_change_radius(minirt, 1);
	else if (keycode == 20)
		ft_change_height(minirt, -1);
	else if (keycode == 21)
		ft_change_height(minirt, 1);
	else if (keycode == 27)
		ft_change_brightness(minirt, -1);
	else if (keycode == 24)
		ft_change_brightness(minirt, 1);
	else if (keycode == 17)
		ft_apply_texture(minirt);
	else if (keycode == 11)
		ft_apply_bump(minirt);
	else if (keycode == 8)
		ft_apply_checkerboard(minirt);
}

static int	ft_hook(int keycode, t_minirt *minirt)
{
	ft_orientation_hook(keycode, minirt);
	ft_manipulation_hook(keycode, minirt);
	return (0);
}

void	ft_register_hooks(t_minirt *minirt)
{
	mlx_mouse_hook(minirt->win, fl_select_object, minirt);
	mlx_key_hook(minirt->win, ft_exit_hook, minirt);
	mlx_hook(minirt->win, 17, 1L << 17, ft_red_cross_hook, minirt);
	mlx_hook(minirt->win, 2, 0L, ft_hook, minirt);
}
