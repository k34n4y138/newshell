/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:48:25 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/09 18:04:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (dst);
	if (dst >= src)
		while (len--)
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
	else
		return (ft_memcpy(dst, src, len));
	return (dst);
}
