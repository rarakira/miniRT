/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:04:46 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 15:41:12 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function copies 'len' bytes from 'src' to 'dst'.
The two strings may overlap.

The function returns the original value of 'dst'. */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < len)
	{
		if (((unsigned char *)src + i) == ((unsigned char *)dst))
		{
			while (len > 0)
			{
				len--;
				((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
			}
			return (dst);
		}
		else
			i++;
	}
	return (ft_memcpy(dst, src, len));
}
