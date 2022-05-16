//
// Created by Dmitry Novikov on 25.01.2022.
//


#include <stdlib.h>

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/objects.h"

static void	ft_print_ambient(t_minirt *minirt)
{
		printf("\033[35m\n########## AMBIENT ##########\n");
		printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
		printf("[RGB] r: %d, g: %d, b: %d\n",
			   minirt->ambient->rgb.r,
			   minirt->ambient->rgb.g,
			   minirt->ambient->rgb.b);
		printf("[COLOR] %X\n", minirt->ambient->colour);
		printf("---------- ------- ----------\n"COLOR_END);

}

void	ft_init_ambient(t_minirt *minirt)
{
	minirt->ambient = malloc(sizeof(t_ambient));
	if (!minirt->ambient)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
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
	minirt->ambient->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->ambient->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->ambient->rgb.b = ft_atoi(&line[++i]);
	minirt->ambient->colour = ft_rgb_hex(0, minirt->ambient->rgb);
//	printf("[RATIO] %f\n", minirt->ambient->lighting_ratio);
//	printf("[COLOR] r: %d, g: %d, b: %d\n", r, g, b);
//	minirt->ambient->colour = fl_rgb_hex(r, g, b);
	ft_print_ambient(minirt);
}
