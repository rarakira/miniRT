/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 13:09:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/20 11:05:35 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	issep(char const *s, char c)
{
	unsigned int	count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c)
			count++;
		else
			return (count);
	}
	return (count);
}

static unsigned int	count_strings(char const *s, char c)
{
	unsigned int	count;
	unsigned int	i;
	size_t			len;

	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i += issep(s + i, c);
			count++;
		}
		else
			i++;
	}
	len = ft_strlen(s);
	if (s[0] == c)
		count--;
	if (s[len - 1] == c && count > 0)
		count--;
	return (count);
}

static char	*create_str(char **str, char c)
{
	size_t	count;
	char	*ptr;

	count = 0;
	while (**str == c)
		*str = (*str + 1);
	while (((*str)[count] != c) && ((*str)[count] != '\0'))
		count++;
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	if (ptr)
	{
		ft_memcpy(ptr, *str, count);
		ptr[count] = '\0';
		*str = (*str + count);
	}
	return (ptr);
}

/* Allocates (with malloc) and returns an array of strings obtained by
splitting ’s’ using the character ’c’ as a delimiter. The array is ended
by a NULL pointer. */
char	**ft_split(char const *s, char c)
{
	unsigned int	n_str;
	unsigned int	i;
	char			*str;
	char			**ptr;

	if (!s || *s == 0)
		return ((char **)ft_calloc(1, sizeof(char *)));
	n_str = count_strings(s, c);
	ptr = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (!ptr)
		return (NULL);
	ptr[n_str] = NULL;
	i = 0;
	str = (char *)s;
	while (i < n_str)
	{
		ptr[i] = create_str(&str, c);
		if (!ptr[i])
		{
			ft_split_free(ptr);
			return (NULL);
		}
		i++;
	}
	return (ptr);
}
