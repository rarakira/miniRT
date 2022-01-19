/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 19:08:00 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/14 23:56:28 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_sign(double *sn, double *n, t_args *arg)
{
	double		sign_bit;
	void		*sign_p;

	sign_p = n;
	sign_bit = (*(long long *)sign_p >> 63);
	if (sign_bit < 0)
	{
		arg->sign = '-';
		*sn *= -1;
		*n *= -1;
	}
}

char	*ft_itoa_f(double n, t_args *arg)
{
	unsigned int		len;
	unsigned long int	mod;
	double				sn;

	if (n == (1.0 / 0.0) || n == (-1.0 / 0.0) || n != n)
	{
		arg->padding = ' ';
		arg->prec = 0;
		arg->prec_flag = 0;
		arg->flag_0 = 0;
		if (n != n)
			return (ft_strdup("nan"));
		if (n < 0)
			arg->sign = '-';
		return (ft_strdup("inf"));
	}
	mod = 10;
	len = 1;
	sn = n;
	check_sign(&sn, &n, arg);
	while ((unsigned long int) sn % mod != (unsigned long int) sn && len++)
		mod *= 10;
	return (build_float(n, sn, arg, len));
}
