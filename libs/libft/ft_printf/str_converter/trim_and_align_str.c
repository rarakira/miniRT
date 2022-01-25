/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_and_align_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:32:00 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:32:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*trim_and_align_str(char *str, t_args *arg, int *count)
{
	char	*res;

	res = NULL;
	if (ft_strlen(str) < arg->width)
	{
		res = (char *)ft_calloc(arg->width + 1, sizeof(char));
		if (res == NULL)
		{
			*count = -1;
			return (NULL);
		}
		ft_memset(res, ' ', arg->width);
		if (!arg->a_left)
		{
			ft_memset(res, arg->padding, arg->width);
			ft_memcpy((res + arg->width - arg->prec), str, arg->prec);
		}
		else
			ft_memcpy(res, str, arg->prec);
		free(str);
	}
	else
		return (str);
	return (res);
}
