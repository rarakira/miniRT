/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:22:17 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/28 18:10:11 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Adds the element ’new’ at the end of the list. */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst)
	{
		if (*lst && new)
		{
			tmp = ft_lstlast(*lst);
			tmp->next = new;
		}
		else
		{
			if (*lst && !new)
			{
				new = ft_lstnew(NULL);
				(*lst)->next = new;
			}
			if (!(*lst) && new)
				*lst = new;
		}
	}
}
