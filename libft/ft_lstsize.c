/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 18:44:07 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 18:48:49 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*itr_hold;

	itr_hold = lst;
	size = 0;
	while (itr_hold)
	{
		size++;
		itr_hold = itr_hold->next;
	}
	return (size);
}
