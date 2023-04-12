/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:22:02 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/08 17:35:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dup;
	size_t	step;

	if (!s || !f)
		return (0);
	dup = ft_strdup(s);
	step = 0;
	if (!dup)
		return (dup);
	while (dup[step])
	{
		dup[step] = (*f)(step, s[step]);
		step++;
	}
	return (dup);
}
