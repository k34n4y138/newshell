/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:33:13 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/23 16:37:59 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizers/tokenizers.h"
#include <stdio.h>
#include <stdlib.h>
void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %d, value: %s\n", tokens->type, tokens->token);
		tokens = tokens->next;
	}
}

void	destroy_tokens(t_token	*tokens)
{
	t_token *tmp;
	
	while (tokens)
	{
		if (tokens->raw)
			free(tokens->raw);
		if (tokens->token)
			free(tokens->token);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);

	}
}

t_command	*parse_command(char *line)
{
	t_token		*tokens;
	t_command	*command;
	
	// pretokenize line
	tokens = tokenizer(line, false);
	// syntaxify tokens, (look for unclosed quotes, unexpected tokens, etc.)
	if (syntaxifier(tokens))
	{
		destroy_tokens(tokens);
		return (NULL);
	}
	// expand DBLQ and VARS, remove quotes
	expand_literal_tokens(tokens);
	// in general, $var is subtokenized into literal tokens split by [SPACES]", special case when command is "export" and token before $var has = in it, then $var is a single token
			//	rely on the fact that the tokens resembling the command and  will already by merged, the token before $var will have = in it and not separated by space from $var,
	// merge literal tokens without space
	merge_tokens(tokens);

	/// start work from here 
	print_tokens(tokens);
	return (command);
}
