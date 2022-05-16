/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:10:24 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:15:11 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/error.h"
#include "../../includes/parsing.h"

t_light	*ft_light_init(t_scene *scene)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		ft_error(EM_MALLOC_LIGHT, scene);
	ft_memset(light, 0, sizeof(t_light));
	return (light);
}

t_object	*ft_object_init(t_scene *scene)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		ft_error(EM_MALLOC_OBJECT, scene);
	ft_memset(object, 0, sizeof(t_object));
	return (object);
}

t_light	**ft_lights_init(int i, t_scene *scene)
{
	t_light		**lights;

	lights = malloc(sizeof(t_light) * i);
	if (!lights)
		ft_error(EM_MALLOC_LGHT_ARR, scene);
	ft_memset(lights, 0, sizeof(t_light) * i);
	return (lights);
}

t_object	**ft_objects_init(int i, t_scene *scene)
{
	t_object	**objects;

	objects = malloc(sizeof(t_object) * i);
	if (!objects)
		ft_error(EM_MALLOC_OBJS_ARR, scene);
	ft_memset(objects, 0, sizeof(t_object) * i);
	return (objects);
}
