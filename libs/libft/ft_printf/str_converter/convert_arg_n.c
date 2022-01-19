/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg_n.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:31:33 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:31:35 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*convert_arg_n(t_args *arg, va_list ap, int *count)
{
	void	*addr;

	if (arg->mod_l == 1)
		addr = va_arg(ap, long *);
	else if (arg->mod_l == 2)
		addr = va_arg(ap, long long *);
	else if (arg->mod_h == 1)
		addr = va_arg(ap, short *);
	else if (arg->mod_h == 2)
		addr = va_arg(ap, signed char *);
	else
		addr = va_arg(ap, int *);
	if (arg->mod_l == 1)
		*(long *)addr = (long)*count;
	else if (arg->mod_l == 2)
		*(long long *)addr = (long long)*count;
	else if (arg->mod_h == 1)
		*(short *)addr = (short)*count;
	else if (arg->mod_h == 2)
		*(signed char *)addr = (signed char)*count;
	else
		*(int *)addr = (int)*count;
	return (NULL);
}
