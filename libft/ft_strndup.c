/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:17:38 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/11 01:23:40 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Duplicate a string from a given index to another
/// @param str The string to duplicate
/// @param from The index to start duplicating from
/// @param to The index to stop duplicating at
/// @return The duplicated string
char	*ft_strndup(char *str, int from, int to)
{
	char	*ret;
	int		i;

	i = 0;
	if (from > to)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (to - from + 1));
	if (!ret)
		return (NULL);
	while (from < to)
	{
		ret[i] = str[from];
		i++;
		from++;
	}
	ret[i] = '\0';
	return (ret);
}
