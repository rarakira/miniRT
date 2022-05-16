/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 12:53:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/18 13:11:46 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	translate_nums(char *num, long long n, unsigned int len)
{
	if (n < -9223372036854775807)
	{
		ft_memcpy(num, "9223372036854775808", len);
		return ;
	}
	if (n == 0)
		num[--len] = '0';
	while (n)
	{
		num[--len] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
}

char	*ft_itoa_d(long long n, char	*sign)
{
	char				*num;
	unsigned int		len;
	unsigned long long	mod;
	long long			sn;

	mod = 10;
	len = 1;
	sn = n;
	if (sn < 0)
	{
		*sign = '-';
		sn = -1 * sn;
	}
	while (sn % mod != (unsigned long long) sn)
	{
		mod *= 10;
		len++;
	}
	num = ft_calloc(len + 1, sizeof(char));
	if (num)
		translate_nums(num, sn, len);
	return (num);
}
