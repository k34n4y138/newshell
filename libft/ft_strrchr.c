/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:39:23 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 16:42:25 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	step;

	step = ft_strlen(s);
	while (step || s[step] == (char)c)
	{
		if (s[step] == (char)c)
			return ((char *)s + step);
		step--;
	}
	return ((char *)0);
}
