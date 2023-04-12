/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:26:44 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 22:35:40 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_head;
	t_list	*lst_traverser;

	if (!lst)
		return (0);
	lst_head = ft_lstnew((*f)(lst->content));
	if (!lst_head)
		return (0);
	lst_traverser = lst_head;
	lst = lst->next;
	while (lst)
	{
		lst_traverser->next = ft_lstnew((*f)(lst->content));
		lst_traverser = lst_traverser->next;
		if (!lst_traverser)
		{
			ft_lstclear(&lst_head, del);
			return (0);
		}
		lst = lst->next;
	}
	return (lst_head);
}
