//
// Created by Dmitry Novikov on 25.01.2022.
//

#include "parsing.h"

static float ft_atof_get_sign(char *str, int *i)
{
	int		mult;

	mult = 1.0;
	if (str[*i] == '-')
		mult = -1.0;
	if (str[*i] == '-' || str[*i] == '+')
		*i += 1;
	return (mult);
}

static int ft_atof_get_integer(char *str, int *i, int *devider)
{
	int		integer;

	integer = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		integer *= 10;
		integer += str[*i] - '0';
		*devider *= 10;
		*i += 1;
	}
	if (str[*i] == '.')
		*i += 1;
	return (integer);
}

float ft_atof(char *str, int *i)
{
	float	tmp;
	float	mult;
	int		integer;
	int		fract;
	int 	divider;

	tmp = 0.0;
	mult = ft_atof_get_sign(str, i);
	divider = 0;
	integer = ft_atof_get_integer(str, i, &divider);
	divider = 1;
	fract = ft_atof_get_integer(str, i, &divider);
	tmp = mult * ((float)integer + (float)fract / divider);
	if (str[*i] == ',')
		*i += 1;
	return (tmp);
}
