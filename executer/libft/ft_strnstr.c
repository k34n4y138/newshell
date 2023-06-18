/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:25:17 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:17:47 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *ha, const char *ne, size_t	len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ne[i] == 0)
		return ((char *)ha);
	while (ha[i] && j + i < len)
	{
		while (ha[i] == ne[i] && j + i < len)
		{
			i++;
			if (ne[i] == '\0')
				return ((char *)ha);
		}
		ha++;
		i = 0;
		j++;
	}
	return (0);
}
