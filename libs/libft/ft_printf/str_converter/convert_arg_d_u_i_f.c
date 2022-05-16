/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg_d_u_i_f.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:31:39 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:31:40 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_arg_string_d_i(t_args *arg, va_list ap)
{
	char	*res;

	if (arg->mod_l == 1)
		res = ft_itoa_d((long long)va_arg(ap, long), &arg->sign);
	else if (arg->mod_l == 2)
		res = ft_itoa_d(va_arg(ap, long long), &arg->sign);
	else if (arg->mod_h == 1)
		res = ft_itoa_d((short)va_arg(ap, int), &arg->sign);
	else if (arg->mod_h == 2)
		res = ft_itoa_d((signed char)va_arg(ap, int), &arg->sign);
	else
		res = ft_itoa_d((long long)va_arg(ap, int), &arg->sign);
	return (res);
}

static char	*get_arg_string_u(t_args *arg, va_list ap)
{
	char	*res;

	if (arg->mod_l == 1)
		res = ft_itoa_u((unsigned long long)va_arg(ap, unsigned long));
	else if (arg->mod_l == 2)
		res = ft_itoa_u(va_arg(ap, unsigned long long));
	else if (arg->mod_h == 1)
		res = ft_itoa_u((unsigned short)va_arg(ap, int));
	else if (arg->mod_h == 2)
		res = ft_itoa_u((unsigned char)va_arg(ap, int));
	else
		res = ft_itoa_u((unsigned long long) va_arg(ap, unsigned int));
	return (res);
}

static char	*get_arg_string(t_args *arg, va_list ap)
{
	char	*res;

	if (arg->format == 'd' || arg->format == 'i')
		res = get_arg_string_d_i(arg, ap);
	if (arg->format == 'u')
		res = get_arg_string_u(arg, ap);
	if (arg->format == 'f')
		res = ft_itoa_f(va_arg(ap, double), arg);
	return (res);
}

char	*convert_arg_d_u_i_f(t_args *arg, va_list ap, int *count)
{
	char	*res;

	res = get_arg_string(arg, ap);
	if (arg->flag_0 && arg->a_left && arg->format == 'f')
	{
		arg->padding = ' ';
		arg->flag_0 = 0;
	}
	if (res == NULL)
	{
		*count = -1;
		return (NULL);
	}
	arg->len = ft_strlen(res);
	if (arg->prec_flag && arg->prec == 0 && *res == '0' && arg->format != 'f')
	{
		*res = '\0';
		arg->len = 0;
	}
	if (arg->prec < arg->len)
		arg->prec = arg->len;
	if (arg->sign)
		arg->prec++;
	return (trim_and_align_digit(res, arg, count));
}
