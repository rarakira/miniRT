/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:24:04 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 17:49:41 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "../includes/minirt.h"
#include "../includes/error.h"

static void	ft_free_lights(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->lights)
	{
		while (scene->lights[i])
		{
			free(scene->lights[i]);
			i++;
		}
		free(scene->lights);
	}
}

static void	ft_free_objects(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->objs)
	{
		while (scene->objs[i])
		{
			free(scene->objs[i]);
			i++;
		}
		free(scene->objs);
	}
}

void	ft_free_scene(t_scene *scene)
{
	ft_free_lights(scene);
	ft_free_objects(scene);
}

void	ft_error(char *error_type, t_scene *scene)
{
	printf(TC_ERROR"Error\n"TC_END);
	printf("%s\n", error_type);
	if (scene)
		ft_free_scene(scene);
	exit(1);
}
