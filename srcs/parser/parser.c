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

//int fl_rgb_hex(int r, int g, int b)
//{
//	int figure_color;
//
//	figure_color = 0;
//	r = (figure_color & (0xFF << 16)) >> 16;
//	g = (figure_color & (0xFF << 8)) >> 8;
//	b = figure_color & 0xFF;
//}

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
	if (line[i] == 'A' && line[i + 1] == ' ')
		ft_read_ambient(minirt, line);
	if (line[i] == 'C' && line [i + 1] == ' ')
		ft_read_camera(minirt, line);
	printf("%s\n", line);
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
	free(line);
}
