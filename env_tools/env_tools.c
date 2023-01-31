/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:41:44 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/30 13:17:56 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_tools.h"

t_list	*env_new(char *key, char *val)
{
	t_env	*pack;
	t_list	*node;

	pack = ft_calloc(1, sizeof(t_env));
	if (!pack)
		return (NULL);
	pack->key = key;
	pack->val = val;
	node = ft_lstnew(pack);
	if (!node)
		free(pack);
	return (node);
}

