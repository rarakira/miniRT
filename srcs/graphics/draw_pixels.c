/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:27:42 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/28 21:46:23 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	dst = minirt->addr + (y * minirt->line_length
			+ x * (minirt->bits_per_pixel));
	*(unsigned int *)dst = color;
}
