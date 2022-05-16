/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:30:42 by lbaela            #+#    #+#             */
/*   Updated: 2022/02/08 16:30:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objects.h"

t_rgb	calc_rgb_light(t_rgb colour, double light)
{
	t_rgb	new;

	new.r = (int)((double)colour.r * light);
	new.g = (int)((double)colour.g * light);
	new.b = (int)((double)colour.b * light);
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
	t_rgb	colour;

	colour.r = a.r * b.r / 255;
	colour.g = a.g * b.g / 255;
	colour.b = a.b * b.b / 255;
	return (colour);
}

t_rgb	add_rgb_light(t_rgb a, t_rgb b)
{
	t_rgb	colour;

	colour.r = a.r + b.r;
	colour.g = a.g + b.g;
	colour.b = a.b + b.b;
	if (colour.r > 255)
		colour.r = 255;
	if (colour.g > 255)
		colour.g = 255;
	if (colour.b > 255)
		colour.b = 255;
	return (colour);
}
