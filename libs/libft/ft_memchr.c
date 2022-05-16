/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:11:37 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 15:49:40 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function locates the first occurrence of 'c' in string 's'.

It returns a pointer to the byte located, or NULL if 'c' does not exist within
'n' bytes. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	size_t			i;

	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)s)[i] == ch)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
