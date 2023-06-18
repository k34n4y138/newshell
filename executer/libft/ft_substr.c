/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:31:03 by yowazga           #+#    #+#             */
/*   Updated: 2022/10/22 22:23:49 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int st, size_t len)
{
	char	*str;
	size_t	i;

	if (st > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	i = 0;
	if (s)
	{
		str = malloc(len + 1);
		if (!str)
			return (0);
		while (st < ft_strlen(s) && len--)
		{
			str[i] = s[st];
			i++;
			st++;
		}
		str[i] = 0;
		return (str);
	}
	return (0);
}
