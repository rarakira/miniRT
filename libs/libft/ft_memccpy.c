/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:06:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 15:35:21 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function copies up to 'n' bytes from string 'src' to string 'dst'.

If the character 'c' occurs in the string 'src', the copy stops and a pointer
to the byte after the 'copy of c' in the string 'dst' is returned.

If 'n' bytes are copied, a NULL pointer is returned.
If 'src' and 'dst' overlap the behavior is undefined. */
void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		if (((unsigned char *)src)[i] == (unsigned char)c)
		{
			return (dst + ++i);
		}
		i++;
	}
	return (NULL);
}
