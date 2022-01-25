/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_f_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:32:04 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/18 19:32:04 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	translate_rem(char *num, double n, unsigned int len)
{
	int		i;

	i = 0;
	while (len--)
	{
		num[i++] = ((long)n % 10) + '0';
		n = (n - ((long)n % 10)) * 10;
	}
	if ((n - (unsigned long int) n) > 0 && (int)n == 5)
		n = 6;
	return ((int)n);
}

static void	check_next_digit(char **num, int len, int n, int round)
{
	char	*tmp;

	while (len >= 0 && (n > 4 || *(*num + len) == '.'))
	{
		if (*(*num + len) == '.')
			len--;
		if (*(*num + len) < '9')
		{
			if ((*(*num + len) - '0') % 2 || round)
				*(*num + len) += 1;
			break ;
		}
		else
			*(*num + len--) = '0';
		if (*(*num + (len + 1)) == '0' && (len + 1) == 0)
		{
			tmp = *num;
			*num = ft_strjoin("1", tmp);
			free (tmp);
		}
	}
}

static char	*get_remainder(char **num, double n, unsigned long int sn,
t_args *arg)
{
	char	*rem;
	char	*join;
	int		next;

	if (!arg->prec_flag)
		arg->prec = 6;
	rem = ft_calloc(arg->prec + 1, sizeof(char));
	if (rem && *num)
		next = translate_rem(rem, (n - sn) * 10, arg->prec);
	join = ft_strjoin(*num, rem);
	if (join)
		check_next_digit(&join, ft_strlen(join) - 1, next, next > 0);
	free(*num);
	free(rem);
	return (join);
}

char	*build_float(double n, unsigned long int sn, t_args *arg,
unsigned int len)
{
	char	*num;

	if ((arg->prec_flag && arg->prec != 0) || arg->flag_alt || !arg->prec_flag)
	{
		num = ft_calloc(len + 2, sizeof(char));
		if (num)
			num[len] = '.';
		arg->flag_alt = 0;
	}
	else
		num = ft_calloc(len + 1, sizeof(char));
	if (num)
		translate_nums(num, sn, len);
	if (arg->prec_flag && arg->prec == 0)
	{
		check_next_digit(&num, (int)(len - 1),
			(int)((n - sn) * 10), ((n - sn) > 0.5));
		return (num);
	}
	return (get_remainder(&num, n, sn, arg));
}
