/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:33:10 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/18 12:43:36 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	clean_up(char **str, t_fd *current, t_fd **start)
{
	t_fd	*tmp;

	tmp = *start;
	free(*str);
	*str = NULL;
	if (current == NULL)
		return (-1);
	if (tmp == current)
		*start = current->next;
	else
	{
		while (tmp->next != current)
			tmp = tmp->next;
	}
	free(*str);
	if (tmp->next)
		tmp->next = tmp->next->next;
	free(current->rem);
	free(current);
	return (-1);
}

char	*has_new_line(char **str)
{
	size_t			i;

	i = 0;
	if (*str == NULL)
		return (0);
	while (*(*str + i) != '\0')
	{
		if (*(*str + i) == '\n')
			return ((char *)(*str + i));
		i++;
	}
	return (NULL);
}

int	get_line(t_fd *current, char **dest, t_fd **start)
{
	char	*tmp;
	char	*sep;

	sep = has_new_line(&current->rem);
	if (!sep)
	{
		*dest = ft_strdup(current->rem);
		clean_up(&current->rem, current, start);
		if (*dest == NULL)
			return (-1);
		return (0);
	}
	*sep = '\0';
	*dest = ft_strdup(current->rem);
	tmp = ft_strdup(++sep);
	if (tmp == NULL || *dest == NULL)
	{
		free(tmp);
		return (clean_up(dest, current, start));
	}
	free(current->rem);
	current->rem = tmp;
	return (1);
}

t_fd	*get_current(t_fd	**start, int fd)
{
	t_fd	*tmp;

	tmp = *start;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = (t_fd *)malloc(sizeof(t_fd));
	if (tmp)
	{
		tmp->fd = fd;
		tmp->next = *start;
		*start = tmp;
		tmp->rem = (char *)malloc(sizeof(char));
		if (tmp->rem)
			tmp->rem[0] = 0;
	}
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	static t_fd		*start = NULL;
	t_fd			*current;
	ssize_t			read_res;
	char			*buf;
	char			*tmp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || !line || !buf)
		return (clean_up(&buf, NULL, &start));
	current = get_current(&start, fd);
	read_res = 1;
	while (!has_new_line(&current->rem) && read_res > 0)
	{
		read_res = read(fd, buf, BUFFER_SIZE);
		if (read_res < 0)
			return (clean_up(&buf, current, &start));
		buf[read_res] = '\0';
		tmp = ft_strjoin(current->rem, buf);
		if (!tmp)
			return (-1);
		free(current->rem);
		current->rem = tmp;
	}
	free(buf);
	return (get_line(current, line, &start));
}
