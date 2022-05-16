/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:34:02 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 15:56:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function writes 'len' bytes of value 'c' to the string 'b'. */
void	*ft_memset(void *b, int c, size_t len)
{
	while (len > 0)
		((unsigned char *)b)[--len] = (unsigned char)c;
	return (b);
}
