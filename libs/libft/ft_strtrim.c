/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:08:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/29 11:50:27 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/* Allocates (with malloc) and returns a copy of ’s1’ with the characters
specified in ’set’ removed from the beginning and the end of the string. */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start < end && inset(s1[start], set))
		start++;
	while (end > start && inset(s1[end], set))
		end--;
	if (end - start)
		return (ft_substr(s1, start, end - start + 1));
	return (ft_substr(s1, start, 0));
}
