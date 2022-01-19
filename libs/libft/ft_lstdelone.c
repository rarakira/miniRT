/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:37:24 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/28 14:47:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes as a parameter an element 'lst' and frees the memory of the element’s
content using the function ’del’ given as a parameter and free the element.
The memory of ’next’ must not be freed.

'lst' – element to free.
'del' of the function used to delete the content.*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free (lst);
}
