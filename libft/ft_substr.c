/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:33:26 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 22:25:24 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	step;
	size_t	s_len;
	size_t	r_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	r_len = s_len - start;
	if (r_len > len)
		r_len = len;
	if (start >= s_len)
		r_len = 0;
	result = (char *)ft_calloc(r_len + 1, sizeof(char));
	if (!result)
		return (0);
	step = 0;
	while (step < r_len)
	{
		result[step] = s[start + step];
		step++;
	}
	return (result);
}
