/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:59:26 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/20 16:36:41 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

#include "mlx.h"
#include "libft.h"
#include "minirt.h"
#include "camera.h"
#include "parsing.h"
#include "objects.h"
#include "error_msgs.h"
#include "ft_printf.h"

# define COLOR_ERROR "\033[31m"
# define COLOR_OK "\033[32m"
# define COLOR_END "\033[0m"

# define SUCCES 0
# define ERROR_FILE_OPEN 1

# define ERROR_RGB -1

int	free_minirt(t_minirt *minirt)
{
	int		i;

	i = 0;
	while (minirt->objs[i])
		free(minirt->objs[i++]);
	free(minirt->objs);
	return (1);
}

static inline void	init_scene(t_minirt *minirt)
{
	t_vector	*sphere_c;
	t_object	*sphere;
//	t_vector	*cam_v;
//	t_vector	*cam_dir;
	int			n_obj = 4;

//	cam_v = new_vect(0, 0, 0);
//	cam_dir = new_vect(0, 0, -1);
//	minirt->camera = create_camera(cam_v, cam_dir, 70);
	minirt->objs = malloc(sizeof(t_object *) * (n_obj + 1));
	if (minirt->objs == NULL || minirt->camera == NULL)
		exit_on_error(-1, ERR_MALLOC);
	/* add 'n_obj' spheres for test */
	n_obj = 0;
	sphere_c = new_vect(3, 6, -32);
	sphere = new_sphere(sphere_c, 12 / 2, COL_VIOLET);
	minirt->objs[n_obj++] = sphere;
	sphere_c = new_vect(-5, 4, -33);
	sphere = new_sphere(sphere_c, 14 / 2, COL_BLUE);
	minirt->objs[n_obj++] = sphere;
	sphere_c = new_vect(6.5, -5.5, -30.5);
	sphere = new_sphere(sphere_c, 6 / 2, COL_YELLOW);
	minirt->objs[n_obj++] = sphere;
	sphere_c = new_vect(2, -3, -34);
	sphere = new_sphere(sphere_c, 16 / 2, COL_RED);
	minirt->objs[n_obj++] = sphere;
	minirt->objs[n_obj] = NULL;
	/* add spheres end */
}

static inline void	init_mlx(t_minirt *minirt)
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

//void ft_parsing(char *argv, t_minirt *objects);

int	main(int argc, char **argv)
{
	t_minirt	minirt;
	int			fd;

	(void) argv;

	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || fd < 0
		|| !ft_strnstr(argv[1], ".rt", ft_strlen(argv[1]))
			)
	{
		printf("Error \n");
		printf(COLOR_ERROR"Failed to open file\n"COLOR_END);
		return (ERROR_FILE_OPEN);
	}
	//init minirt;
	ft_init_ambient(&minirt);
	ft_init_camera(&minirt);
	// parse
	ft_parsing(argv[1], &minirt);
	printf(COLOR_OK"OK\n"COLOR_END);
	//end parsing
	init_scene(&minirt);
	init_mlx(&minirt);
	register_hooks(&minirt);
	ray_tracing(&minirt);
	mlx_put_image_to_window(minirt.mlx, minirt.win, minirt.img, 0, 0);
	mlx_loop(minirt.mlx);

	ft_free_camera(&minirt);
	free_minirt(&minirt);
//	write(2, ERR_ARGS, ft_strlen(ERR_ARGS));

	return (0);
}
