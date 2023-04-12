/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:18:16 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/11 01:51:37 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Split a string into tokens
/// @param str The string to split
/// @param token The token to split the string with
/// @return The next token in the string
char	*ft_strtok(char *str, char *tokens)
{
	static char	*save;
	static char	*orig;
	int			iter;
	char		*ret;

	if (str && str != orig)
		orig = str;
	if (!save)
		save = orig;
	if (!save)
		return (NULL);
	iter = 0;
	while (save[iter] && !ft_strchr(tokens, save[iter]))
		iter++;
	if (!save[iter])
	{
		ret = ft_strdup(save);
		save = NULL;
		orig = NULL;
		return (ret);
	}
	ret = ft_strndup(save, 0, iter);
	save = save + iter + 1;
	return (ret);
}
