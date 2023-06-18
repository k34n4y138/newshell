/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:55:46 by yowazga           #+#    #+#             */
/*   Updated: 2022/12/21 10:56:26 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned long long nb, char c, int *count)
{
	if (nb >= 16)
	{
		ft_puthex(nb / 16, c, count);
		ft_puthex(nb % 16, c, count);
	}
	else
	{
		if (nb < 10)
			ft_putchar(nb + 48, count);
		else
		{
			if (c == 'x')
				ft_putchar(nb - 10 + 'a', count);
			else
				ft_putchar(nb - 10 + 'A', count);
		}
	}
}
