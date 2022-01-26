/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:56 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 13:20:28 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/parsing.h"

//t_object	*new_sphere(t_vector *center, float radius, int colour)
//{
//	t_object	*sphere;
//
//	sphere = malloc(sizeof(t_object));
//	if (sphere == NULL)
//		exit_on_error(-1, ERR_MALLOC);
//	ft_memset(sphere, 0, sizeof(t_object));
//	sphere->center = center;
//	sphere->radius = radius;
//	sphere->type = 'S';
//	sphere->colour = colour;
//	sphere->next = 0;
//	sphere->previous = 0;
//	return (sphere);
//}

void	ft_read_sphere(t_minirt *minirt, char *line)
{
	int	i;

	i = 3;
	minirt->objs_lst->type = 'S';
	while (line[i++] == ' ');
	minirt->objs_lst->center->x = ft_atof(line, &i);
	minirt->objs_lst->center->y = ft_atof(line, &i);
	minirt->objs_lst->center->z = ft_atof(line, &i);
	while (line[i++] == ' ');
	minirt->objs_lst->radius = ft_atof(line, &i) / 2;
	while (line[i++] == ' ');
	minirt->objs_lst->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.b = ft_atoi(&line[++i]);
	minirt->objs_lst->colour = ft_rgb_hex(0, minirt->objs_lst->rgb);
}
