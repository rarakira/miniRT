/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:18:17 by dredfort          #+#    #+#             */
/*   Updated: 2022/03/01 20:16:14 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include "../../includes/parsing.h"
#include "../../includes/error.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)b;
	i = 0;
	while (i < len)
		tmp[i++] = (char)c;
	return (b);
}

void	ft_check_next_parametr(char *str, int i, t_scene *scene)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < '0' || str[i] > '9')
		ft_error(EM_BAD_FORMAT, scene);
}

void	ft_count_separators(char *str, int *i, char *separator)
{
	while (str[*i] == ' ')
		*i += 1;
	if (str[*i] == ',')
	{
		*separator += 1;
		*i += 1;
	}
	while (str[*i] == ' ')
	{
		*i += 1;
	}
}

t_vector	ft_parsing_vector(char *str, int *i, t_scene *scene)
{
	t_vector	matrix;
	char		separator;

	separator = 0;
	while (str[*i] == ' ')
		*i += 1;
	matrix.x = ft_atof(str, i);
	ft_count_separators(str, i, &separator);
	matrix.y = ft_atof(str, i);
	ft_count_separators(str, i, &separator);
	matrix.z = ft_atof(str, i);
	if (separator != 2)
		ft_error(EM_VCT_FORMAT, scene);
	return (matrix);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	size_t	i;
	char	*ptr;

	if (*needle == '\0')
		return ((char *)haystack);
	n_len = ft_strlen(needle);
	i = 0;
	ptr = NULL;
	while ((len - i) >= n_len && !ptr)
	{
		if (!ft_strncmp(haystack + i, needle, n_len))
			ptr = (char *)(haystack + i);
		if (haystack[i] == '\0')
			break ;
		i++;
	}
	return (ptr);
}
