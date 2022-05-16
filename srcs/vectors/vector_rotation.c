/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:31:04 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 18:18:11 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vector	ft_vector_rotate_cw(t_vector vector)
{
	float	tmp;

	tmp = vector.z;
	vector.z = vector.y;
	vector.y = vector.x;
	vector.x = tmp;
	return (vector);
}

t_vector	ft_vector_rotate_ccw(t_vector vector)
{
	float	tmp;

	tmp = vector.x;
	vector.x = vector.y;
	vector.y = vector.z;
	vector.z = tmp;
	return (vector);
}
