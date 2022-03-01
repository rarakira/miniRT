/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:59:26 by lbaela            #+#    #+#             */
/*   Updated: 2022/03/01 20:10:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "../includes/minirt.h"
#include "../includes/error.h"
#include "../includes/parsing.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	int			fd;

	if (argc < 2)
		ft_error(EM_NO_ARG, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		ft_error(EM_FILE_OPEN, 0);
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])))
		ft_error(EM_NO_SCENE_FILE, 0);
	ft_memset(&scene, 0, sizeof(t_scene));
	ft_parsing_scene(fd, ft_longest_line(open(argv[1], O_RDONLY)), &scene);
	ft_prepare_scene(&scene);
	ft_graphic_layer(&scene);
	return (0);
}
