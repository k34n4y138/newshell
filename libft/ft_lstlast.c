/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:49:38 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 18:52:32 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*itr_hold;

	itr_hold = lst;
	while (itr_hold)
	{
		if (!itr_hold->next)
			return (itr_hold);
		itr_hold = itr_hold->next;
	}
	return (itr_hold);
}
