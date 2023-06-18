/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:09:29 by yowazga           #+#    #+#             */
/*   Updated: 2022/10/22 21:55:10 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	str = malloc (size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}
