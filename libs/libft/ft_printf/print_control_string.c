/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_control_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:26:24 by lbaela            #+#    #+#             */
/*   Updated: 2021/06/17 15:33:51 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fetch_fspec(char **s)
{
	size_t	n;
	char	*res;

	n = 0;
	while (!ft_isalpha(*(*s + n)) && (*(*s + n)) != '%' && (*(*s + n)) != '\0')
		n++;
	while (*(*s + n) == 'l' || *(*s + n) == 'h')
		n++;
	if ((*(*s + n)) == '\0')
		return (NULL);
	n++;
	res = ft_substr(*s, 0, n);
	*s += n;
	return (res);
}

int	print_control_string(char *s, va_list ap, int *count)
{
	char	*fspec;

	while (*s != '\0')
	{
		while (*s != '\0' && *s != '%')
		{
			ft_putchar_fd(*s++, 1);
			*count += 1;
		}
		if (*s == '%')
		{
			s++;
			fspec = fetch_fspec(&s);
			if (fspec == NULL)
				return (-1);
			print_arg(fspec, ap, count);
			free(fspec);
		}
	}
	return (0);
}
