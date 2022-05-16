/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:43:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 16:11:40 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*  Function appends string 'src' to the end of 'dst'. 'dstsize' – is size of
src buffer.

The string will be NUL-terminated unless dstsize is 0 or the original 'dst'
string was longer than dstsize.

It returns the total length of the string it tried to create: the 'initial 
length of dst' + 'length of src'. */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_len;
	size_t	d_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (d_len > dstsize)
		return (dstsize + s_len);
	ft_strlcpy(dst + d_len, src, dstsize - d_len);
	return (s_len + d_len);
}
