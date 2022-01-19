/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 21:08:37 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/27 14:07:22 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the integer ’n’ to the given file descriptor. */
void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	len;
	long int		mod;
	char			ch;
	long int		nn;

	mod = 10;
	len = 1;
	nn = (long int)n;
	if (nn < 0)
	{
		write(fd, "-", 1);
		nn *= -1;
	}
	while (nn % mod != nn)
	{
		mod *= 10;
		len++;
	}
	while (mod >= 10)
	{
		mod /= 10;
		ch = (nn / mod) + '0';
		nn = nn % mod;
		write(fd, &ch, 1);
	}
}
