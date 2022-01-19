/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:28:40 by lbaela            #+#    #+#             */
/*   Updated: 2021/04/28 19:06:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterates the list ’lst’ and applies the function ’f’ to the content of each
element. Creates a new list resulting of the successive applications of the
function ’f’. The ’del’ function is used to delete the content of an element
if needed */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin_lst;
	t_list	*tmp;
	t_list	*map;

	if (!lst)
		return (NULL);
	tmp = ft_lstnew(f(lst->content));
	if (!tmp)
		return (NULL);
	begin_lst = tmp;
	map = lst->next;
	while (map)
	{
		tmp = ft_lstnew(f(map->content));
		if (!tmp)
		{
			ft_lstclear(&begin_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&begin_lst, tmp);
		map = map->next;
	}
	return (begin_lst);
}
