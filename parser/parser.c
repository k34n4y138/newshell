/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:33:13 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 18:36:09 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizers/tokenizers.h"
#include <stdio.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %d, value: %s\n", tokens->type, tokens->raw);
		tokens = tokens->next;
	}
}



t_command	*parse_command(char *line)
{
	t_token		*tokens;
	t_command	*command;

	tokens = tokenizer(line);
	tokens_expander(tokens);
	print_tokens(tokens);
	return (command);
}
