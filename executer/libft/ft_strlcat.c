/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:36:24 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:20:08 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	slen;
	size_t	dlen;

	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (slen);
	dlen = ft_strlen(dst);
	j = dlen;
	if (dstsize > dlen)
	{
		while (j < dstsize - 1 && src[i])
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
		return (slen + dlen);
	}
	else
		return (dstsize + slen);
}
