/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:05:56 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 17:09:40 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	step;

	step = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while (step < dstsize - 1 && src[step])
	{
		dst[step] = src[step];
		step++;
	}
	dst[step] = 0;
	return (ft_strlen(src));
}
