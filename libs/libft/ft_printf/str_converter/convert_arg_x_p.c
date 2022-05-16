/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg_x_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:31:22 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:31:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_arg_string(t_args *arg, va_list ap)
{
	char	*res;

	if (arg->format == 'x' || arg->format == 'X')
	{
		if (arg->mod_l == 1)
			res = ft_itoa_x(va_arg(ap, long), arg);
		else if (arg->mod_l == 2)
			res = ft_itoa_x(va_arg(ap, long long), arg);
		else if (arg->mod_h == 1)
			res = ft_itoa_x((unsigned short)va_arg(ap, int), arg);
		else if (arg->mod_h == 2)
			res = ft_itoa_x((unsigned char)va_arg(ap, int), arg);
		else
			res = ft_itoa_x((long int) va_arg(ap, int), arg);
	}
	if (arg->format == 'p')
		res = ft_itoa_p(va_arg(ap, unsigned long int), arg);
	return (res);
}

char	*convert_arg_x_p(t_args *arg, va_list ap, int *count)
{
	char	*res;

	res = get_arg_string(arg, ap);
	if (res == NULL)
	{
		*count = -1;
		return (NULL);
	}
	arg->len = ft_strlen(res);
	if ((arg->prec_flag && *res == '0')
		&& (arg->prec == 0 || arg->format == 'p'))
	{
		*res = '\0';
		arg->len = 0;
	}
	if (arg->prec < arg->len)
		arg->prec = arg->len;
	if (arg->sign)
		arg->sign = 0;
	return (trim_and_align_digit(res, arg, count));
}
