/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:33:30 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/20 15:20:52 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspace(int ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n')
		return (1);
	if (ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	return (0);
}

static int	check_base(int n, int base)
{
	char	str_l[16];
	char	str_u[16];
	int		i;

	ft_memcpy(str_l, "0123456789abcdef", 16);
	ft_memcpy(str_u, "0123456789ABCDEF", 16);
	i = 0;
	while (i < base)
	{
		if (n == str_l[i] || n == str_u[i])
			return (1);
		i++;
	}
	return (0);
}

static int	base_converter(int n, int base)
{
	char	str_l[16];
	char	str_u[16];
	int		i;

	ft_memcpy(str_l, "0123456789abcdef", 16);
	ft_memcpy(str_u, "0123456789ABCDEF", 16);
	i = 0;
	while (i < base)
	{
		if (n == str_l[i] || n == str_u[i])
			return (i);
		i++;
	}
	return (-1);
}

/* Function converts the initial portion of the string pointed to by 'str'
to int representation in specified BASE. */
int	ft_atoi_base(const char *str, int base)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((isspace(str[i])) && str[i] != '\0')
	{
		if (isspace(str[i]))
			i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (base == 16 && str[i] == '0' && str[i + 1] == 'x')
		i = i + 2;
	while (str[i] != '\0' && check_base(str[i], base))
		result = result * base + base_converter(str[i++], base);
	return (result * sign);
}
