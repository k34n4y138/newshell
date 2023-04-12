/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:01:25 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 17:05:55 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			step;
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *)s1;
	_s2 = (unsigned char *)s2;
	step = 0;
	while (step < n)
	{
		if (_s1[step] != _s2[step])
			return (_s1[step] - _s2[step]);
		step++;
	}
	return (0);
}
