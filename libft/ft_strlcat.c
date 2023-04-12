/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:12:48 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 22:28:06 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	step;
	size_t	dst_len;

	step = 0;
	if (!dstsize)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	if (dstsize <= dst_len)
		return (ft_strlen(src) + dstsize);
	while (src[step] && step < dstsize - dst_len - 1)
	{
		dst[dst_len + step] = src[step];
		step++;
	}
	dst[dst_len + step] = 0;
	return (dst_len + ft_strlen(src));
}
