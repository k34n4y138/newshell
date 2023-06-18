/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 22:08:28 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/18 17:14:36 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_arg(va_list list, const char *str, int i, int *count)
{
	if (str[i + 1] == '%')
		ft_putchar('%', count);
	else if (str[i + 1] == 'c')
		ft_putchar(va_arg(list, int), count);
	else if (str[i + 1] == 's')
		ft_putstr(va_arg(list, char *), count);
	else if (str[i + 1] == 'p')
		ft_putadd(va_arg(list, void *), count);
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
		ft_putnbr(va_arg(list, int), count);
	else if (str[i + 1] == 'u')
		ft_putnbr(va_arg(list, unsigned int), count);
	else if (str[i + 1] == 'x')
		ft_puthex(va_arg(list, unsigned int), 'x', count);
	else if (str[i + 1] == 'X')
		ft_puthex(va_arg(list, unsigned int), 'X', count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	list;

	i = -1;
	count = 0;
	va_start(list, str);
	while (str[++i])
	{
		if (str[i] != '%')
			ft_putchar(str[i], &count);
		else
		{
			ft_arg(list, str, i, &count);
			i++;
		}
	}
	va_end(list);
	return (count);
}
