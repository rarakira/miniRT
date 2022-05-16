/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:06:04 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 16:01:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function locates the first '(char)c' in the string pointed to by 's'.

Terminating `\0' is considered to be part of the string; if 'c' is `\0',
the functions locate the terminating `\0'. */
char	*ft_strchr(const char *s, int c)
{
	size_t	srcsize;

	srcsize = ft_strlen(s);
	return ((char *)ft_memchr(s, c, srcsize + 1));
}
