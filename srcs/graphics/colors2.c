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

t_rgb	ft_get_rgb(int r, int g, int b)
{
	t_rgb	tmp;

	tmp.r = r;
	tmp.g = g;
	tmp.b = b;
	return (tmp);
}

t_rgb	ft_rgb2gray(t_rgb rgb)
{
	unsigned char	gray;

	gray = 0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b;
	return (ft_get_rgb(gray, gray, gray));
}

t_rgb	ft_rgb_brightness_adjustment(t_rgb rgb, float adjust)
{
	rgb.r *= adjust;
	rgb.g *= adjust;
	rgb.b *= adjust;
	if (rgb.r > 255)
		rgb.r = 255;
	if (rgb.g > 255)
		rgb.g = 255;
	if (rgb.b > 255)
		rgb.b = 255;
	return (rgb);
}
