//
// Created by Dmitry Novikov on 26.01.2022.
//
#include "../../includes/parsing.h"

void	ft_read_cylinder(t_minirt *minirt, char *line)
{
	int	i;

	i = 2;
	minirt->objs_lst->type = 'C';
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->center->x = ft_atof(line, &i);
	minirt->objs_lst->center->y = ft_atof(line, &i);
	minirt->objs_lst->center->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->norm_v->x = ft_atof(line, &i);
	minirt->objs_lst->norm_v->y = ft_atof(line, &i);
	minirt->objs_lst->norm_v->z = ft_atof(line, &i);
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->radius = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->height = ft_atof(line, &i) / 2;
	while (line[i] == ' ')
		i++;
	minirt->objs_lst->rgb.r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.g = ft_atoi(&line[++i]);
	while (ft_isdigit(line[i]))
		i++;
	minirt->objs_lst->rgb.b = ft_atoi(&line[++i]);
	minirt->objs_lst->colour = ft_rgb_hex(0, minirt->objs_lst->rgb);
}
