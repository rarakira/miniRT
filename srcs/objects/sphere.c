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

#include "libft.h"
#include "minirt.h"
#include "objects.h"
#include "error_msgs.h"

t_object	*new_sphere(t_vector *center, float radius, int colour)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		exit_on_error(-1, ERR_MALLOC);
	ft_memset(sphere, 0, sizeof(t_object));
	sphere->center = center;
	sphere->radius = radius;
	sphere->type = 'S';
	sphere->colour = colour;
	return (sphere);
}
