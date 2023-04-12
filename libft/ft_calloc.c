/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:58:24 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/09 16:01:55 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	detect_overflow(size_t c, size_t s)
{
	size_t	r;

	r = c * s;
	if (s && r / s != c)
		return (1);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (detect_overflow(count, size))
		return (0);
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
