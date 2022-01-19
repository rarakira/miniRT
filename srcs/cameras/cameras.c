/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:48:46 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:46:22 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minirt.h"
#include "camera.h"
#include "error_msgs.h"

t_camera	*create_camera(t_vector *org, t_vector *dir, float angle)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	if (cam == NULL)
		exit_on_error(-1, ERR_MALLOC);
	cam->origin = org;
	cam->direction = dir;
	cam->angle = angle;
	return (cam);
}
