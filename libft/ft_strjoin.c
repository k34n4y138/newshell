/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 21:50:06 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 18:45:07 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	dst_len;
	char	*result;

	if (!s1 || !s2)
		return (0);
	dst_len = ft_strlen(s1) + ft_strlen(s2) +1;
	result = (char *)ft_calloc(dst_len, sizeof(char));
	if (!result)
		return (result);
	ft_strlcpy(result, s1, dst_len);
	ft_strlcat(result, s2, dst_len);
	return (result);
}
