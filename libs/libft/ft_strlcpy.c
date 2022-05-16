/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:39:57 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/28 14:46:03 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function copies up to (dstsize - 1) characters from the string 'src' to
'dst', NUL-terminating the result if dstsize is not 0. */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	if (!src || !dst)
		return (0);
	srclen = ft_strlen(src);
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= srclen)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	else
	{
		ft_memcpy(dst, src, srclen);
		dst[srclen] = '\0';
	}
	return (srclen);
}
