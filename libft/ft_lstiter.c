/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:43:36 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 21:47:48 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_traverser;

	if (!f || !lst)
		return ;
	lst_traverser = lst;
	while (lst_traverser)
	{
		(*f)(lst_traverser->content);
		lst_traverser = lst_traverser->next;
	}
}
