/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg_s.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 20:52:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/14 23:57:51 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_string(t_args *arg, va_list ap)
{
	char	*res;
	char	*tmp;

	tmp = ft_strdup(va_arg(ap, char *));
	if (!tmp)
		tmp = ft_strdup("(null)");
	if (!arg->prec_flag || ft_strlen(tmp) < arg->prec || arg->prec_neg)
		arg->prec = ft_strlen(tmp);
	if (ft_strlen(tmp) > arg->prec && arg->prec_flag)
	{
		res = (char *)ft_calloc(arg->prec + 1, sizeof(char));
		ft_strlcpy(res, tmp, arg->prec + 1);
		free(tmp);
	}
	else
		res = tmp;
	if (arg->width < arg->prec)
		arg->width = arg->prec;
	return (res);
}

char	*convert_arg_s(t_args *arg, va_list ap, int *count)
{
	char	*res;

	arg->padding = ' ';
	res = get_string(arg, ap);
	if (!res)
	{
		*count = -1;
		return (NULL);
	}
	return (trim_and_align_str(res, arg, count));
}
