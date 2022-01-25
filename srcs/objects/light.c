//
// Created by Dmitry Novikov on 25.01.2022.
//

#include <stdlib.h>

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/objects.h"

void	ft_print_light(t_minirt *minirt)
{
	printf("\033[36m\n########## LIGHT ##########\n");
	printf("[POINT] x: %f, y: %f, z: %f\n",
		   minirt->light->point->x,
		   minirt->light->point->y,
		   minirt->light->point->z);
	printf("[BRIGHTNESS] %f\n", minirt->light->brightness_ratio);
	printf("[RGB] r: %d, g: %d, b: %d\n",
		   minirt->light->rgb.r,
		   minirt->light->rgb.g,
		   minirt->light->rgb.b);
	printf("---------- ----- ----------\n"COLOR_END);
}

void	ft_init_light(t_minirt *minirt)
{
	minirt->light = malloc(sizeof(t_light));
	if (!minirt->light)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_LIGHT);
	}
	minirt->light->point = malloc(sizeof(t_vector));
	if (!minirt->light->point)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		free(minirt->light);
		exit(ERROR_MALLOC_LIGHT_ORIGIN);
	}
}

void	ft_read_light(t_minirt *minirt, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	i = 1;
	while (line[i] == ' ')
		i++;
	minirt->light->point->x = ft_atof(line, &i);
	minirt->light->point->y = ft_atof(line, &i);
	minirt->light->point->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->light->brightness_ratio = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->light->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->light->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->light->rgb.b = ft_atoi(&line[++i]);
//	printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
//	printf("[COLOR] r: %d, g: %d, b: %d\n", r, g, b);
//	minirt->ambient->colour = fl_rgb_hex(r, g, b);
	ft_print_light(minirt);
}
