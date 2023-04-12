/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:59:54 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 17:22:52 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	calc_strlen(int n)
{
	size_t	size;

	size = 0;
	if (n < 0)
	{
		if (n == -2147483648)
			return (0);
		size++;
		n *= -1;
	}
	while (n / 10 > 0)
	{
		size++;
		n /= 10;
	}
	return (size + 1);
}

static char	*return_min_int(void)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)ft_calloc(12, sizeof(char));
	if (!ptr)
		return (ptr);
	i = 0;
	while ("-2147483648"[i])
	{
		ptr[i] = "-2147483648"[i];
		i++;
	}
	return (ptr);
}

static int	get_max_pwr(int n)
{
	int	pwr;

	pwr = 1;
	while (n / (pwr * 10) > 0)
	{
		pwr *= 10;
		if (pwr == 1000000000)
			return (pwr);
	}
	return (pwr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	step;
	int		remainder;
	int		pwr;

	if (calc_strlen(n) == 0)
		return (return_min_int());
	ptr = (char *)ft_calloc(calc_strlen(n) + 1, sizeof(char));
	if (!ptr)
		return (ptr);
	step = 0;
	if (n < 0)
	{
		ptr[step++] = '-';
		n *= -1;
	}
	remainder = 0;
	pwr = get_max_pwr(n);
	while (pwr)
	{
		ptr[step++] = (n / pwr) - (remainder * 10) + 48;
		remainder = n / pwr;
		pwr /= 10;
	}
	return (ptr);
}
