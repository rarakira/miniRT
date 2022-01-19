/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:24:04 by lbaela            #+#    #+#             */
/*   Updated: 2022/01/19 09:41:45 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"
#include "error_msgs.h"

void	exit_on_error(int err, char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(err);
}
