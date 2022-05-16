/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:30:42 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 16:30:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_rgb	calc_rgb_light(t_rgb color, double light)
{
	t_rgb	new;

	new.r = (int)((double)color.r * light);
	new.g = (int)((double)color.g * light);
	new.b = (int)((double)color.b * light);
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return (new);
}

t_rgb	multiply_rgbs(t_rgb a, t_rgb b)
{
	t_rgb	color;

	color.r = a.r * b.r / 255;
	color.g = a.g * b.g / 255;
	color.b = a.b * b.b / 255;
	return (color);
}

t_rgb	add_rgb_light(t_rgb a, t_rgb b)
{
	t_rgb	color;

	color.r = a.r + b.r;
	color.g = a.g + b.g;
	color.b = a.b + b.b;
	if (color.r > 255)
		color.r = 255;
	if (color.g > 255)
		color.g = 255;
	if (color.b > 255)
		color.b = 255;
	return (color);
}

t_rgb	invert_color(t_rgb color)
{
	return ((t_rgb){255 - color.r, 255 - color.g, 255 - color.b});
}

int	ft_rgb_hex(int t, t_rgb rgb)
{
	return (t << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}
