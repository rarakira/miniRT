/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_layer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:33:23 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:29:10 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../../libs/minilibx_macos/mlx.h"
#include "../../includes/minirt.h"
#include "../../includes/error.h"

static t_pattern	ft_get_pattern(t_minirt *minirt, char *filename)
{
	t_pattern	tmp;

	tmp.img = 0;
	tmp.addr = 0;
	if (filename)
		tmp.img = mlx_xpm_file_to_image(minirt->mlx, filename,
				&tmp.width, &tmp.height);
	if (tmp.img)
		tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel,
				&tmp.size_line, &tmp.endian);
	if (!tmp.img || !tmp.addr)
		printf(TC_ERROR"Failed to load %s pattern"TC_END"\n", filename);
	return (tmp);
}

void	ft_gl_init(t_minirt *minirt, t_scene *scene)
{
	minirt->size_x = WIN_WIDTH;
	minirt->size_y = WIN_HEIGHT;
	minirt->mlx = mlx_init();
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	minirt->img = mlx_new_image(minirt->mlx, WIN_WIDTH, WIN_HEIGHT);
	minirt->addr = mlx_get_data_addr(minirt->img, &minirt->bits_per_pixel,
			&minirt->line_length, &minirt->endian);
	minirt->bits_per_pixel /= 8;
	minirt->scene = *scene;
	minirt->texture = ft_get_pattern(minirt, "./patterns/texture.xpm");
	minirt->bump = ft_get_pattern(minirt, "./patterns/bump.xpm");
	minirt->apply_texture = 0;
	minirt->apply_bump = 0;
	minirt->apply_checkerboard = 0;
}

void	ft_graphic_layer(t_scene *scene)
{
	t_minirt	minirt;

	ft_gl_init(&minirt, scene);
	ray_tracing(&minirt);
	mlx_put_image_to_window(minirt.mlx, minirt.win, minirt.img, 0, 0);
	ft_register_hooks(&minirt);
	mlx_loop(minirt.mlx);
}
