/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:42 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 11:35:05 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

static int	offscreen(int x, int y)
{
	if (x < 0 || x >= WIN_WIDTH)
		return (1);
	if (y < 0 || y >= WIN_HEIGHT)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_minirt *minirt, int x, int y, int color)
{
	char	*dst;

	if (offscreen(x, y))
		return ;
	dst = minirt->addr + (y * minirt->line_length + x * (minirt->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_background(t_minirt *minirt)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(minirt, x, y, COL_YELLOW);
			x++;
		}
		y++;
	}
}
