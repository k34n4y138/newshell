/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 22:49:20 by zmoumen           #+#    #+#             */
/*   Updated: 2022/10/09 14:28:20 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_strs(char const *s, char c)
{
	size_t	steps;
	size_t	count;

	count = 0;
	steps = 0;
	while (s[steps])
	{
		while (s[steps] && s[steps] == c)
			steps++;
		if (s[steps])
			count++;
		while (s[steps] && s[steps] != c)
			steps++;
	}
	return (count);
}

static size_t	size_till_seplen(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (s[size] && s[size] != c)
		size++;
	return (size);
}

static char	**panic_exit(char **ptr, size_t j)
{
	while (j >= 0)
		free(ptr[j--]);
	free(ptr);
	return (0);
}

static int	aux_strdup(char **ptr, char const *s, char c)
{
	*ptr = (char *)ft_calloc(size_till_seplen(s, c) + 1, sizeof(char));
	if (!*ptr)
		return (0);
	ft_strlcpy(*ptr, s, size_till_seplen(s, c) + 1);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	ptr = (char **)ft_calloc(calc_strs(s, c) + 1, sizeof(char *));
	if (!ptr)
		return (ptr);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			if (!aux_strdup(&ptr[j++], &s[i], c))
				return (panic_exit(ptr, --j));
		while (s[i] && s[i] != c)
			i++;
	}
	return (ptr);
}
