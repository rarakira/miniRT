/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_and_align_digit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:32:08 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:32:09 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	if_alt(char *str, char f)
{
	if (f == 'p')
		f = 'x';
	while (*str)
	{
		if (*str == '0')
		{
			str[1] = f;
			return ;
		}
		str++;
	}
}

static char	*set_new_line(t_args *arg)
{
	char	*res;

	if (arg->width > arg->prec)
	{
		res = (char *)ft_calloc(arg->width + 1, sizeof(char));
		ft_memset(res, arg->padding, arg->width);
		if (arg->len < arg->prec && !arg->a_left)
			ft_memset(res + arg->width - arg->prec, '0', arg->prec);
		if (arg->len < arg->prec && arg->a_left)
			ft_memset(res, '0', arg->prec);
	}
	else
	{
		res = (char *)ft_calloc(arg->prec + 1, sizeof(char));
		ft_memset(res, '0', arg->prec);
		arg->width = arg->prec;
	}
	if (arg->flag_alt)
		if_alt(res, arg->format);
	return (res);
}

static void	value_align_right(char *dest, char *src, t_args *arg)
{
	if (arg->sign)
	{
		if ((arg->flag_0 && arg->format == 'f')
			|| (arg->flag_0 && !arg->prec_flag))
			*dest = arg->sign;
		else
			dest[arg->width - arg->prec--] = arg->sign;
	}
	ft_memcpy((dest + arg->width - arg->len), src, arg->len);
}

static void	value_align_left(char *dest, char *src, t_args *arg)
{
	if (arg->sign)
	{
		*dest = arg->sign;
		if (arg->prec > arg->len)
			ft_memcpy(dest + arg->prec - arg->len, src, arg->len);
		else
			ft_memcpy(dest + 1, src, arg->prec);
	}
	else
	{
		if (arg->prec > arg->len)
			ft_memcpy(dest + arg->prec - arg->len, src, arg->len);
		else
			ft_memcpy(dest, src, arg->prec);
	}
}

char	*trim_and_align_digit(char *str, t_args *arg, int *count)
{
	char	*res;

	res = NULL;
	if (((arg->flag_alt && *str != '0') && *str != '\0')
		|| (arg->format == 'p' && (*str == '0' || arg->prec_flag)))
		arg->prec += 2;
	else if (arg->flag_alt && *str == '0')
		arg->flag_alt = 0;
	if (arg->len < arg->width || arg->len < arg->prec)
	{
		res = set_new_line(arg);
		if (res == NULL)
		{
			*count = -1;
			return (NULL);
		}
		if (!arg->a_left)
			value_align_right(res, str, arg);
		else
			value_align_left(res, str, arg);
		free(str);
	}
	else
		return (str);
	return (res);
}
