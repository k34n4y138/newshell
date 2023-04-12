/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:17:35 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 21:26:23 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_hld;
	t_list	*node_next;

	if (!lst)
		return ;
	node_hld = *lst;
	while (node_hld)
	{
		node_next = node_hld->next;
		ft_lstdelone(node_hld, del);
		node_hld = node_next;
	}
	*lst = 0;
}
