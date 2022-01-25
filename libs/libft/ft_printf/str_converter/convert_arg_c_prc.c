/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg_c_prc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:31:43 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:31:45 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_spaces(t_args *arg, int *count)
{
	while (arg->width-- > 1)
	{
		*count += 1;
		ft_putchar_fd(' ', 1);
	}
}

static void	print_eol(t_args *arg, int *count)
{
	if (!arg->a_left)
	{
		print_spaces(arg, count);
		ft_putchar_fd('\0', 1);
	}
	else
	{
		ft_putchar_fd('\0', 1);
		print_spaces(arg, count);
	}
	*count += 1;
}

char	*convert_arg_c_prc(t_args *arg, va_list ap, int *count)
{
	char	*res;

	res = ft_calloc(2, sizeof(char));
	if (!res)
	{
		*count = -1;
		return (NULL);
	}
	if (arg->format == 'c')
		*res = va_arg(ap, int);
	if (arg->format == '%')
		*res = '%';
	if (*res == '\0')
	{
		print_eol(arg, count);
		free(res);
		return (NULL);
	}
	arg->prec = 1;
	return (trim_and_align_str(res, arg, count));
}
