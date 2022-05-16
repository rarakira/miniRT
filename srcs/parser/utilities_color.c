/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:03:16 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 18:34:17 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/error.h"

static int	ft_adjust_channel(int channel)
{
	int	tmp;

	if (channel > 255)
		tmp = 255;
	else if (channel < 0)
		tmp = 0;
	else
		tmp = channel;
	return (tmp);
}

t_rgb	ft_adjust_rgb(t_rgb color)
{
	t_rgb	tmp;

	tmp.r = ft_adjust_channel(color.r);
	tmp.g = ft_adjust_channel(color.g);
	tmp.b = ft_adjust_channel(color.b);
	return (tmp);
}

int	ft_rgb2hex(char t, t_rgb color)
{
	return (t << 24 | color.r << 16 | color.g << 8 | color.b);
}

t_rgb	ft_parsing_color(char *str, int i, t_scene *scene)
{
	t_rgb	color;
	char	separator;

	separator = 0;
	while (str[i] == ' ')
		i++;
	color.r = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	ft_count_separators(str, &i, &separator);
	color.g = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	ft_count_separators(str, &i, &separator);
	if (!str[i] || str[i] < '0' || str[i] > '9')
		separator--;
	color.b = ft_atoi(&str[i]);
	while (str[i] == ' ' || (str[i] >= '0' && str[i] <= '9'))
			i++;
	if (str[i] || separator != 2)
		ft_error(EM_RGB_FORMAT, scene);
	return (color);
}
