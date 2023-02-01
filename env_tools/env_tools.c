/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:41:44 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/01 15:33:19 by zmoumen          ###   ########.fr       */
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

char	*expand_variable(char	*key)
{
	
	return (ft_strdup("polo"));
}