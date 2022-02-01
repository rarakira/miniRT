/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:32:15 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/31 20:51:27 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "objects.h"
#include "ft_printf.h"

int	switch_obj(t_object **objs)
{
	g_obj_n += 1;
	if (objs[g_obj_n] == NULL)
		g_obj_n = 0;
	ft_printf("Select is set to [%d:%c]\n", g_obj_n, objs[g_obj_n]->type);
	return (1);
}

void	move_obj(int keycode, t_object **objs)
{
	if (keycode == 126)
		objs[g_obj_n]->center->y += 0.5;
	if (keycode == 125)
		objs[g_obj_n]->center->y -= 0.5;
	if (keycode == 124)
		objs[g_obj_n]->center->x += 0.5;
	if (keycode == 123)
		objs[g_obj_n]->center->x -= 0.5;
	ft_printf("Moving [%d:%c] x = %f, y = %f\n", g_obj_n, objs[g_obj_n]->type, objs[g_obj_n]->center->x, objs[g_obj_n]->center->y);
}

int	key_hook(int keycode, t_minirt *minirt)
{
	if (keycode)
	{
		ft_printf("Hello from key_hook - [%d]!\n", keycode);
		if (keycode == 31)
			return (switch_obj(minirt->objs));
		if (keycode == 126 || keycode == 125
			|| keycode == 124 || keycode == 123)
			move_obj(keycode, minirt->objs);
	}
	mlx_clear_window(minirt->mlx, minirt->win);
	ray_tracing(minirt);
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
	return (1);
}
