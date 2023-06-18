/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:16:20 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:19:07 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		len += 1;
		return (len);
	}
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_inter(char *s, long n, int i)
{
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (n)
	{
		s[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*str;

	i = 0;
	nb = n;
	i = ft_len(nb);
	str = malloc(i * sizeof(char ) + 1);
	if (!str)
		return (0);
	str[i--] = 0;
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	ft_inter(str, nb, i);
	return (str);
}
