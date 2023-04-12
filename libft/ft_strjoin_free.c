/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:06:20 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/11 15:18:01 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief join two strings and free the ones you want
/// @param s1 string 1
/// @param s2 string 2
/// @param f1 free s1
/// @param f2 free s2
/// @return the joined string
char	*ft_strjoin_free(char *s1, char *s2, int f1, int f2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (ret);
}
