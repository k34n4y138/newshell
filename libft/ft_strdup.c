/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 19:14:57 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 19:32:23 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_size;
	size_t	cp_step;
	char	*s2;

	s1_size = ft_strlen(s1);
	s2 = (char *)ft_calloc(s1_size + 1, sizeof(char));
	cp_step = 0;
	if (!s2)
		return (s2);
	while (cp_step < s1_size)
	{
		s2[cp_step] = s1[cp_step];
		cp_step++;
	}
	s2[cp_step] = 0;
	return (s2);
}
