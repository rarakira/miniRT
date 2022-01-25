/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 09:32:15 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:48:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "ft_printf.h"

int	key_hook(int keycode, t_minirt *minirt)
{
	if (keycode)
	{
		ft_printf("Hello from key_hook - [%d]!\n", keycode);
		return (0);
	}
	mlx_clear_window(minirt->mlx, minirt->win);
	// re-render
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img, 0, 0);
	return (1);
}
