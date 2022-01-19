/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:50:45 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/14 11:38:57 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	inset(char ch, char const *set)
{
	int	i;

	i = 0;
	while (*set)
	{
		if (*set++ == ch)
			return (1);
	}
	return (0);
}

void	check_for_mods(t_args *arg, char **fspec)
{
	int	len;

	len = (int) ft_strlen(*fspec);
	if (len > 1)
		len -= 2;
	while ((*(*fspec + len) == 'l' || *(*fspec + len) == 'h') && len >= 0)
	{
		if (*(*fspec + len) == 'l')
			arg->mod_l += 1;
		else if (*(*fspec + len) == 'h')
			arg->mod_h += 1;
		len--;
	}
}

void	check_for_flags(t_args *arg, char **fspec)
{
	while (inset(**fspec, "-+0 #"))
	{
		if (**fspec == '-')
			arg->a_left = 1;
		else if (**fspec == '0')
		{
			arg->padding = '0';
			arg->flag_0 = 1;
		}
		else if (**fspec == '#' && (arg->format == 'x' || arg->format == 'X'
				|| arg->format == 'f'))
			arg->flag_alt = 1;
		else if (**fspec == '+' && arg->sign != '-')
			arg->sign = '+';
		else if (**fspec == ' ' && arg->sign != '+' && arg->sign != '-')
			arg->sign = ' ';
		*fspec += 1;
	}
}
