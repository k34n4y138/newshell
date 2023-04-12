/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:33:26 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 22:33:32 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	step;
	size_t	n_len;

	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (0);
	n_len = ft_strlen(needle);
	step = 0;
	while (haystack[step] && (len - step) >= n_len)
	{
		if (!ft_strncmp(haystack + step, needle, n_len))
			return ((char *)haystack + step);
		step++;
	}
	return ((char *)0);
}
