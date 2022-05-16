/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:57:01 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/02 09:51:38 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/error.h"

char	ft_check_color(t_rgb c)
{
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		return (1);
	else
		return (0);
}

char	ft_check_orientation(t_vector v)
{
	if (v.x < -1 || v.x > 1 || v.y < -1 || v.y > 1 || v.z < -1 || v.z > 1)
		return (1);
	else
		return (0);
}

void	ft_parsing_ambient(t_scene *scene, char *str, int i)
{
	if (scene->counter.ambients)
		ft_error(EM_AMBIENT_DECL, scene);
	scene->ambient.brightness = ft_atof(str, &i);
	ft_check_next_parametr(str, i, scene);
	if (scene->ambient.brightness < 0 || scene->ambient.brightness > 1)
		ft_error(EM_AMBIENT_LIGHT, scene);
	scene->ambient.rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->ambient.rgb))
		ft_error(EM_AMBIENT_COLOR, scene);
	scene->counter.ambients++;
}

void	ft_parsing_camera(t_scene *scene, char *str, int i)
{
	if (scene->counter.cameras)
		ft_error(EM_CAMERA_DECL, scene);
	scene->camera.point = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->camera.orientation = ft_parsing_vector(str, &i, scene);
	if (ft_check_orientation(scene->camera.orientation))
		ft_error(EM_CAMERA_ORIENT, scene);
	if (vect_len(scene->camera.orientation) != 1)
		ft_normal_error(EM_CAMERA_NNORM, &scene->camera.orientation);
	ft_check_next_parametr(str, i, scene);
	scene->camera.fov = ft_atof(str, &i);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		ft_error(EM_CAMERA_FOV, scene);
	while (str[i] == ' ')
		i++;
	if (str[i])
		ft_error(EM_BAD_FORMAT, scene);
	scene->counter.cameras++;
}

void	ft_parsing_light(t_scene *scene, char *str, int i)
{
	if (!scene->light)
		scene->light = ft_light_init(scene);
	else
	{
		scene->light->next = ft_light_init(scene);
		scene->light->next->previous = scene->light;
		scene->light = scene->light->next;
	}
	scene->light->point = ft_parsing_vector(str, &i, scene);
	ft_check_next_parametr(str, i, scene);
	scene->light->brightness = ft_atof(str, &i);
	ft_check_next_parametr(str, i, scene);
	if (scene->light->brightness < 0 || scene->light->brightness > 1)
		ft_error(EM_LIGHT_BRIGHT, scene);
	scene->light->rgb = ft_parsing_color(str, i, scene);
	if (ft_check_color(scene->light->rgb))
		ft_error(EM_LIGHT_COLOR, scene);
	scene->counter.lights++;
}
