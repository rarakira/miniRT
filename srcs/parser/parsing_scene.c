/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:50:31 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:11:13 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/error.h"

static void	ft_parsing_scene_properties(t_scene *scene, char *str, int i)
{
	if (str[i] == 'A')
		ft_parsing_ambient(scene, str, i + 1);
	else if (str[i] == 'C')
		ft_parsing_camera(scene, str, i + 1);
	else if (str[i] == 'L')
	{
		ft_parsing_light(scene, str, i + 1);
		ft_light_as_object(scene, scene->light);
	}
}

static void	ft_parsing_scene_objects(t_scene *scene, char *str, int i)
{
	if (!scene->object)
		scene->object = ft_object_init(scene);
	else
	{
		scene->object->next = ft_object_init(scene);
		scene->object->next->previous = scene->object;
		scene->object = scene->object->next;
	}
	if (str[i] == 's' && str[i + 1] == 'p')
		ft_parsing_sphere(scene, str, i + 2);
	else if (str[i] == 'p' && str[i + 1] == 'l')
		ft_parsing_plane(scene, str, i + 2);
	else if (str[i] == 'c' && str[i + 1] == 'y')
		ft_parsing_cylinder(scene, str, i + 2);
	else if (str[i] == 'c' && str[i + 1] == 'o')
		ft_parsing_cone(scene, str, i + 2);
}

static void	ft_parsing_elements(t_scene *scene, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i + 1] && str[i + 1] == ' '
		&& (str[i] == 'A' || str[i] == 'C' || str[i] == 'L'))
		ft_parsing_scene_properties(scene, str, i);
	else if (str[i + 2] && str[i + 2] == ' '
		&& ((str[i] == 's' && str[i + 1] == 'p')
			|| (str[i] == 'p' && str[i + 1] == 'l')
			|| (str[i] == 'c' && str[i + 1] == 'y')
			|| (str[i] == 'c' && str[i + 1] == 'o')))
		ft_parsing_scene_objects(scene, str, i);
	else
	{
		free(str);
		ft_error(EM_BAD_FORMAT, scene);
	}
}

static char	*ft_create_line(int size)
{
	char	*line;

	line = malloc(sizeof(char) * (size + 1));
	if (!line)
		ft_error(EM_MALLOC_LINE, 0);
	ft_memset(line, 0, size + 1);
	return (line);
}

void	ft_parsing_scene(int fd, int longest_line, t_scene *scene)
{
	int		bwr;
	char	symbol;
	char	*line;
	int		i;

	line = ft_create_line(longest_line);
	bwr = 1;
	i = 0;
	while (bwr)
	{
		bwr = read(fd, &symbol, 1);
		if (symbol != '\n')
			line[i++] = symbol;
		else
		{
			line[i] = 0;
			if (i)
				ft_parsing_elements(scene, line);
			i = 0;
		}
	}
	free(line);
	close(fd);
}
