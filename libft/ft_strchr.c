/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:34:03 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 19:37:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	step;

	step = 0;
	while (s[step] || s[step] == (char)c)
	{
		if (s[step] == (char)c)
			return ((char *)s + step);
		step++;
	}
	return ((char *)0);
}
