/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:39:07 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 15:44:50 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	step;

	step = 0;
	if (!dst && !src)
		return (dst);
	while (step < n)
	{
		*((unsigned char *)dst + step) = *((unsigned char *)src + step);
		step++;
	}
	return (dst);
}
