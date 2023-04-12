/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:55:07 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 17:01:00 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	step;

	step = 0;
	while (step < n)
	{
		if (*(unsigned char *)(s + step) == (unsigned char)c)
			return ((void *)(s + step));
		step++;
	}
	return ((void *)0);
}
