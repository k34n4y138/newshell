/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:00:23 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/30 11:49:16 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include "../libft.h"

char	*ctoa(int c)
{
	char	*s;

	s = (char *)ft_calloc(2, 1);
	if (s)
		s[0] = (unsigned char)c;
	return (s);
}

void	ft_putchar_str(char c, char *s)
{
	int	itr;

	itr = ft_strlen(s);
	s[itr] = c;
}

void	aux_ultoa_recursive(unsigned long nb,
	char *base, unsigned long baselen, char *str)
{
	if (nb >= baselen)
	{
		aux_ultoa_recursive(nb / baselen, base, baselen, str);
		ft_putchar_str(base[(nb % baselen)], str);
	}
	else
		ft_putchar_str(base[nb], str);
}

char	*ft_ultoa_base(unsigned long nb, char *base, char *prefix)
{
	char				result[1024];
	unsigned long		baselen;

	baselen = ft_strlen(base);
	ft_bzero(result, 1024);
	ft_strlcat(result, prefix, 1024);
	aux_ultoa_recursive(nb, base, baselen, result);
	return (ft_strdup(result));
}
