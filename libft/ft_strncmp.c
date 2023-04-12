/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:42:52 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/07 16:54:39 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	step;

	step = 0;
	while (step < n)
	{
		if (s1[step] != s2[step] || !s1[step] || !s2[step])
			return ((unsigned char)s1[step] - (unsigned char)s2[step]);
		step++;
	}
	return (0);
}
