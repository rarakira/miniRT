/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:04:40 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:16:35 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../../includes/parsing.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_longest_line(int fd)
{
	int		bwr;
	char	symbol;
	int		len;
	int		max_strlen;

	bwr = read(fd, &symbol, 1);
	len = 0;
	max_strlen = 0;
	while (bwr)
	{
		len++;
		if (symbol == '\n')
		{
			if (len > max_strlen)
				max_strlen = len;
			len = 0;
		}
		bwr = read(fd, &symbol, 1);
	}
	close(fd);
	return (max_strlen);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (0);
}
