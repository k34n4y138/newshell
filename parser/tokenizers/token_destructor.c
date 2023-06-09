/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_destructor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:34:04 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/09 15:51:54 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_token.h"
#include <stdlib.h>

void	destroy_tokens(t_token *tokens)
{
	t_token	*trgt;

	while (tokens)
	{
		trgt = tokens;
		tokens = tokens->next;
		free(trgt->raw);
		free(trgt->token);
		free(trgt);
	}
}
