/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:00:35 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/05 17:54:32 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char *str, int *count)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			write(2, &str[i], 1);
			i++;
			*count += 1;
		}
	}
	else
	{
		write(1, "(null)", 6);
		*count += 6;
	}
}
