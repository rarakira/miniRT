/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:04:40 by dredfort          #+#    #+#             */
/*   Updated: 2022/02/15 18:07:29 by dredfort         ###   ########.fr       */
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
