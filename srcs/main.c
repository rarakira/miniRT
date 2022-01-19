/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:59:26 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 17:18:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "mlx.h"
#include "libft.h"
#include "minirt.h"
#include "camera.h"
#include "objects.h"
#include "error_msgs.h"
#include "ft_printf.h"

t_scene	*new_scene(t_camera *cam, int n_objects)
{
	t_scene		*scene;
	t_object	**objects;

	scene = malloc(sizeof(t_scene));
	objects = malloc(sizeof(t_object *) * (n_objects + 1));
	if (cam == NULL || objects == NULL)
		exit_on_error(-1, ERR_MALLOC);
	ft_memset(scene, 0, sizeof(t_scene));
	scene->cams = cam;
	scene->objs = malloc(sizeof(t_object));
	return (scene);
}

int	free_minirt(t_minirt *minirt)
{
	if (minirt->scene)
	{
		free(minirt->scene->cams);
		free(minirt->scene->objs);
	}
	free(minirt->scene);
	return (1);
}

void	init_minirt(t_minirt *minirt)
{
	t_vector	*sphere_c;
	t_object	*sphere;
	t_vector	*cam_v;
	t_vector	*cam_dir;
	t_camera	*cam;
	int			n_obj = 2;

	cam_v = new_vect(0, 0, 0);
	cam_dir = new_vect(0, 0, -1);
	cam = create_camera(cam_v, cam_dir, 70);
	minirt->scene = new_scene(cam, n_obj);
	/* add 2 spheres for test */
	sphere_c = new_vect(3, 2, -32);
	sphere = new_sphere(sphere_c, 12 / 2, COL_VIOLET);
	minirt->scene->objs[0] = sphere;
	sphere_c = new_vect(-5, -2, -33);
	sphere = new_sphere(sphere_c, 14 / 2, COL_BLUE);
	minirt->scene->objs[1] = sphere;
	minirt->scene->objs[n_obj] = NULL;
	/* add spheres end */
	minirt->scene->width = WIN_WIDTH;
	minirt->scene->height = WIN_HEIGHT;
}

void	init_mlx(t_minirt *minirt)
{
	minirt->mlx = mlx_init();
	if (!minirt->mlx && free_minirt(minirt))
		exit_on_error(1, ERR_MLX);
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "mlx");
	if (!minirt->win && free_minirt(minirt))
		exit_on_error(1, ERR_WIN);
	minirt->img = mlx_new_image(minirt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!minirt->img && free_minirt(minirt))
		exit_on_error(1, ERR_IMG);
	minirt->addr = mlx_get_data_addr(minirt->img, &minirt->bits_per_pixel,
			&minirt->line_length, &minirt->endian);
}

int	main(int argc, char **argv)
{
	t_minirt	minirt;

	(void) argv;
	if (argc == 2)
	{
		// parse
		init_minirt(&minirt);
		init_mlx(&minirt);
		register_hooks(&minirt);
		ray_tracing(&minirt);
		mlx_put_image_to_window(minirt.mlx, minirt.win, minirt.img, 0, 0);
		mlx_loop(minirt.mlx);
	}
	write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
	return (0);
}
