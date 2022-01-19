/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:38:57 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/18 12:28:03 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	translate_u_nums(char *num, unsigned long long n, unsigned int len)
{
	if (n == 0)
		num[--len] = '0';
	while (n)
	{
		num[--len] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
}

char	*ft_itoa_u(unsigned long long n)
{
	char				*num;
	unsigned int		len;
	unsigned long long	mod;

	mod = 10;
	len = 1;
	while (n % mod != n && len < 20)
	{
		mod *= 10;
		len++;
	}
	num = ft_calloc(len + 1, sizeof(char));
	if (num)
		translate_u_nums(num, n, len);
	return (num);
}
