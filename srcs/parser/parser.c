#include "../../includes/parsing.h"

int ft_max_strlen(char *file_name)
{
	int fd;
	int bwr;
	char symbol;
	int len;
	int max_strlen;

	fd = open(file_name, O_RDONLY);
	bwr = read(fd, &symbol, 1);
	len = 0;
	max_strlen = 0;
	while (bwr)
	{
		len++;
		if (symbol == '\n')
		{
			if (len > max_strlen)
				max_strlen = len;
			len = 0;
		}
		bwr = read(fd, &symbol, 1);
	}
	close(fd);
	return (max_strlen);
}

int	ft_rgb_hex(int t, t_rgb rgb)
{
	return (t << 24 | rgb.r << 16 | rgb.g << 8 | rgb.b);
}

static char *ft_create_line(char *file_name)
{
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_max_strlen(file_name) + 1));
	if (!tmp)
	{
		write(2, ERROR_MALLOC, ft_strlen(ERROR_MALLOC));
		exit(ERROR_MALLOC_LINE);
	}
	return (tmp);
}

static void ft_parse_objects(t_minirt *minirt, char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i + 1] && line[i] == 'A' && line[i + 1] == ' ')
		ft_read_ambient(minirt, line);
	if (line[i + 1] && line[i] == 'C' && line [i + 1] == ' ')
		ft_read_camera(minirt, line);
	if (line[i + 1] && line[i] == 'L' && line [i + 1] == ' ')
		ft_read_light(minirt, line);
	if (line[i + 2]
		&& (line[i] == 's' && line [i + 1] == 'p' && line[i + 2] == ' '))
		ft_add_obj_to_lst(minirt, line);
	printf("%s\n", line);
}

void	ft_print_object(t_object *object);

void ft_create_objs_arr(t_minirt *minirt)
{
	int i;
	int j;

	i = 1;
	while (minirt->objs_lst->previous)
		minirt->objs_lst = minirt->objs_lst->previous;
	while (minirt->objs_lst->next)
	{
		minirt->objs_lst = minirt->objs_lst->next;
		i++;
	}
	printf("\n\n>>>>> %d <<<<<\n\n", i);
	minirt->objs = malloc(sizeof(t_object) * (i + 1));
	if (!minirt->objs)
	{
		//error
	}
	ft_memset(minirt->objs, 0, sizeof(t_object) * (i + 1));
	j = 0;
	while (minirt->objs_lst->previous)
		minirt->objs_lst = minirt->objs_lst->previous;
	while (minirt->objs_lst)
	{
		minirt->objs[j] = minirt->objs_lst;
	printf("@@@ %p > %p > %p @@@\n", minirt->objs_lst->previous, minirt->objs_lst, minirt->objs_lst->next);
		minirt->objs_lst = minirt->objs_lst->next;
		j++;
	}
	minirt->objs[j] = 0;

	j = 0;
	while (minirt->objs[j])
	{
		ft_print_object(minirt->objs[j]);
		j++;
	}
}

void ft_print_objs_lst(t_minirt *minirt)
{
	t_object *tmp;

	tmp = minirt->objs_lst;
	while (tmp->previous)
		tmp = tmp->previous;
	while (tmp)
	{
		printf("\033[33m\n########## OBJECT ##########\n");
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
		printf("%p > %p > %p\n", tmp->previous, tmp, tmp->next);
		tmp = tmp->next;
	}
}

void ft_parsing(char *file_name, t_minirt *minirt)
{
	int fd;
	long bwr;
	char symbol;
	char *line;
	int i;

	line = ft_create_line(file_name);
	fd = open(file_name, O_RDONLY);
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
			ft_parse_objects(minirt, line);
			i = 0;
		}
	}
	ft_print_objs_lst(minirt);
	ft_create_objs_arr(minirt);
	free(line);
}
