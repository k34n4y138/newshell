/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 15:54:17 by yowazga           #+#    #+#             */
/*   Updated: 2023/02/04 16:17:50 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i != 0 && ((unsigned char *)str)[i] != (unsigned char)c)
		i--;
	if (((unsigned char *)str)[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (0);
}
