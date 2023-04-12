/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:24:19 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/09 15:53:23 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if ("\t\n\v\f\r "[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	pre_detect_overflow(long long a)
{
	long long	b;

	b = a * 10;
	if (a != b / 10)
		return (1);
	return (0);
}

static int	get_overflow_re(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (pre_detect_overflow(result))
			return (get_overflow_re(sign));
		result *= 10;
		result += (*str) - 48;
		str++;
	}
	return (result * sign);
}
