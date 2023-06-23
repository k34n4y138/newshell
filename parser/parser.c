/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:33:13 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/23 15:44:48 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizers/tokenizers.h"
#include "command_builders/command_builders.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Maestro function for parsing line into a linked list of commands
///			-# it first tokenize the line
///			-# then it checks for syntax errors
///			-# then it expands the literal tokens and merge them
///			-# finally it builds the command chain
t_command	*parse_command(char *line)
{
	t_token		*tokens;
	t_command	*command;

	tokens = tokenizer(line, false);
	if (syntaxifier(tokens))
	{
		destroy_tokens(tokens);
		env_exit_status(258, 1);
		return (NULL);
	}
	expand_literal_tokens(tokens);
	merge_tokens(tokens);
	command = build_commandchain(tokens);
	destroy_tokens(tokens);
	return (command);
}
