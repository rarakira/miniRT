/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:04:26 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/14 14:45:45 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_translate_nums(char *num, long int n, int sign, unsigned int len)
{
	if (sign)
		num[0] = '-';
	if (n == 0)
		num[--len] = '0';
	while (n)
	{
		num[--len] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
}

/* Function converts integers to strings (memory allocated). */
char	*ft_itoa(int n)
{
	char			*num;
	unsigned int	len;
	long int		mod;
	int				sign;
	long int		nn;

	mod = 10;
	sign = 0;
	len = 1;
	nn = n;
	if (nn < 0)
	{
		sign = 1;
		nn *= -1;
		len++;
	}
	while (nn % mod != nn)
	{
		mod *= 10;
		len++;
	}
	num = ft_calloc(len + 1, sizeof(char));
	if (num)
		ft_translate_nums(num, nn, sign, len);
	return (num);
}
