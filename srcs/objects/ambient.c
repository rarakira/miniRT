//
// Created by Dmitry Novikov on 25.01.2022.
//


#include <stdlib.h>

#include "minirt.h"
#include "parsing.h"
#include "objects.h"

void	ft_print_ambient(t_minirt *minirt)
{
		printf("\033[35m\n########## AMBIENT ##########\n");
		printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
		printf("[COLOR] r: %d, g: %d, b: %d\n",
			   minirt->ambient->colour.r,
			   minirt->ambient->colour.g,
			   minirt->ambient->colour.b);
		printf("---------- ------- ----------\n"COLOR_END);

}

void	ft_init_ambient(t_minirt *minirt)
{
	minirt->ambient = malloc(sizeof(t_ambient));
	if (!minirt->ambient)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		exit(ERROR_MALLOC_AMBIENT);
	}
}

void	ft_read_ambient(t_minirt *minirt, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	minirt->ambient->lighting_ratio = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->ambient->colour.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->ambient->colour.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->ambient->colour.b = ft_atoi(&line[++i]);

//	printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
//	printf("[COLOR] r: %d, g: %d, b: %d\n", r, g, b);
//	minirt->ambient->colour = fl_rgb_hex(r, g, b);
	ft_print_ambient(minirt);
}
