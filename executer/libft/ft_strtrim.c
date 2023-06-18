/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:39:46 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:15:11 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		len;

	i = 0;
	if (s1)
	{
		len = ft_strlen(s1);
		while (ft_strchr(set, s1[i]) && s1[i])
			i++;
		while (ft_strchr(set, s1[len -1]) && len > i)
			len--;
		trim = ft_substr(s1, i, len - i);
		if (!trim)
			return (0);
		return (trim);
	}
	return (0);
}
