//
// Created by Dmitry Novikov on 25.01.2022.
//

#include "parsing.h"

static float ft_atof_get_sign(char *line, int *i)
{
	int		mult;

	mult = 1.0;
	if (line[*i] == '-')
		mult = -1.0;
	if (line[*i] == '-' || line[*i] == '+')
		*i += 1;
	return (mult);
}

static int ft_atof_get_integer(char *line, int *i)
{
	int		integer;

	integer = 0;
	while (ft_isdigit(line[*i]))
	{
		integer *= 10;
		integer += line[*i] - '0';
		*i += 1;
	}
	if (line[*i] == '.')
		*i += 1;
	return (integer);
}

static double ft_dig_num(int num)
{
	double	i;

	i = 1;
	while (num)
	{
		num /= 10;
		i *= 10;
	}
	return (i);
}
float ft_atof(char *line, int *i)
{
	float	tmp;
	float	mult;
	int		integer;
	int		fract;

	tmp = 0.0;
	mult = ft_atof_get_sign(line, i);
	integer = ft_atof_get_integer(line, i);
	fract = ft_atof_get_integer(line, i);
	tmp = mult * ((float)integer + (float)fract / ft_dig_num(fract));
	if (line[*i] == ',')
		*i += 1;
	return (tmp);
}
