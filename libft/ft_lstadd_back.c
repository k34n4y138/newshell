/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:53:28 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/30 11:33:28 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newn)
{
	t_list	*last_obj;

	last_obj = ft_lstlast(*lst);
	if (last_obj)
		last_obj->next = newn;
	else
		*lst = newn;
}
