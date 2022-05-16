/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_atoi_atof.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:02:57 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 18:03:02 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	num;

	i = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (num < 0 && sign > 0)
		return (-1);
	else if (num < 0 && sign <= 0)
		return (0);
	else
		return (sign * (int)num);
}

static float	ft_atof_get_sign(char *str, int *i)
{
	int		mult;

	mult = 1.0;
	if (str[*i] == '-')
		mult = -1.0;
	if (str[*i] == '-' || str[*i] == '+')
		*i += 1;
	return (mult);
}

static int	ft_atof_get_integer(char *str, int *i, int *devider)
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

float	ft_atof(char *str, int *i)
{
	float	tmp;
	float	mult;
	int		integer;
	int		fract;
	int		divider;

	while (str[*i] == ' ')
		*i += 1;
	tmp = 0.0;
	mult = ft_atof_get_sign(str, i);
	divider = 0;
	integer = ft_atof_get_integer(str, i, &divider);
	divider = 1;
	fract = ft_atof_get_integer(str, i, &divider);
	tmp = mult * ((float)integer + (float)fract / divider);
	return (tmp);
}
