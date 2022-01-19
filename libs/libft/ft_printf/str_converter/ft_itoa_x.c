/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:53:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/18 13:29:02 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	convert_to_hex(int n, char format)
{
	if (n < 10)
		return (n + '0');
	else
	{
		n -= 10;
		if (format == 'X')
			return ('A' + n);
		return ('a' + n);
	}
}

static void	translate_hex(char *num, unsigned long long n, unsigned int len,
char format)
{
	unsigned long long		rem;
	unsigned long long		res;

	rem = n;
	res = n;
	if (n == 0)
		num[--len] = '0';
	while (res)
	{
		if (res >= 16)
		{
			rem = res % 16;
			res = (res / 16);
			num[--len] = convert_to_hex(rem, format);
		}
		else
		{
			num[--len] = convert_to_hex(res, format);
			res = 0;
		}
	}
}

static unsigned long	get_neg_res(long int n, unsigned int *len,
t_args *arg)
{
	unsigned long	max_v;

	max_v = 18446744073709551615U;
	arg->sign = '-';
	if (arg->mod_l == 0)
	{
		*len = 8;
		return (4294967295 + n + 1);
	}
	else
	{
		*len = 16;
		return (max_v + n + 1);
	}
}

char	*ft_itoa_x(long long n, t_args *arg)
{
	char					*num;
	unsigned int			len;
	unsigned long long		res;

	if (n < -9223372036854775807)
	{
		num = ft_strdup("8000000000000000");
		return (num);
	}
	if (n >= 0)
	{
		res = n;
		len = 1;
		while (res >= 16 && len++)
			res = res / 16;
		res = n;
	}
	else
		res = get_neg_res(n, &len, arg);
	num = ft_calloc(len + 1, sizeof(char));
	if (num)
		translate_hex(num, res, len, arg->format);
	return (num);
}

char	*ft_itoa_p(unsigned long long n, t_args *arg)
{
	char				*num;
	unsigned int		len;
	unsigned long long	res;

	res = n;
	len = 1;
	while (res >= 16 && len++)
		res = res / 16;
	num = ft_calloc(len + 1, sizeof(char));
	if (num)
		translate_hex(num, n, len, arg->format);
	return (num);
}
