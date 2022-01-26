//
// Created by Dmitry Novikov on 26.01.2022.
//
#include "../../includes/parsing.h"

t_object *ft_new_objs_list(t_minirt *minirt)
{
	t_object *tmp;

	tmp = malloc(sizeof(t_object));
	if (!tmp)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		ft_free_camera(minirt);
		free(minirt->light);
		exit(ERROR_MALLOC_OBJECTS_LIST);
	}
	ft_memset(tmp, 0, sizeof(t_object));
	tmp->center = malloc(sizeof(t_vector));
	if (!tmp->center)
	{
		//error func
	}
	ft_memset(tmp->center, 0 ,sizeof(t_vector));
	tmp->norm_v = malloc(sizeof(t_vector));
	if (!tmp->norm_v)
	{
		//error func
	}
	ft_memset(tmp->norm_v, 0 ,sizeof(t_vector));
	tmp->next = 0;
	tmp->previous = 0;
	return (tmp);
}

void	ft_print_object(t_object *object)
{
	t_object *tmp;

	tmp = object;
	printf("\033[40m\n########## OBJECT ##########\n");
	printf("[TYPE] %c\n", tmp->type);
	printf("[CENTER] x: %f, y: %f, z: %f\n",
		   tmp->center->x,
		   tmp->center->y,
		   tmp->center->z);
	printf("[VECTOR] x: %f, y: %f, z: %f\n",
		   tmp->norm_v->x,
		   tmp->norm_v->y,
		   tmp->norm_v->z);
	printf("[RADIUS] %f\n", tmp->radius);
	printf("[HEIGHT] %f\n", tmp->height);
	printf("[RGB] r: %d, g: %d, b: %d\n",
		   tmp->rgb.r,
		   tmp->rgb.g,
		   tmp->rgb.b);
	printf("[COLOR] %X\n", tmp->colour);
	printf("---------- ------ ----------\n"COLOR_END);
}

void ft_read_object(t_minirt *minirt, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 2] && line[i + 2] == ' '
		&& line[i] == 's' && line[i + 1] == 'p' )
		ft_read_sphere(minirt, line);
	else if (line[i + 2] && line[i + 2] == ' '
		&& line[i] == 'p' && line[i + 1] == 'l' )
		ft_read_plane(minirt, line);
	else if (line[i + 2] && line[i + 2] == ' '
		&& line[i] == 'c' && line[i + 1] == 'y' )
		ft_read_cylinder(minirt, line);
	ft_print_object(minirt->objs_lst);
}

void ft_add_obj_to_lst(t_minirt *minirt, char *line)
{
	if (!minirt->objs_lst)
		minirt->objs_lst = ft_new_objs_list(minirt);
	else
	{
		minirt->objs_lst->next = ft_new_objs_list(minirt);
		minirt->objs_lst->next->previous = minirt->objs_lst;
		minirt->objs_lst = minirt->objs_lst->next;
	}
	ft_read_object(minirt, line);
}
