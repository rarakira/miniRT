/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 10:59:46 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/28 22:45:26 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc) and returns a substring from the string ’s’.

The substring begins at index ’start’ and is of maximum size ’len’.

Returns the substring. NULL if the allocation fails */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	src_len;
	char	*dest;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len + 1 || len == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if ((src_len - start) < len)
		len = src_len - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (dest);
	ft_strlcpy(dest, (s + start), len + 1);
	return (dest);
}
