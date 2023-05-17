/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:31:09 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 18:45:02 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TOKEN_H

# define T_TOKEN_H
# include <stdbool.h>

enum	e_tokens
{
	TOK_UNSET = 0x00,
	TOK_LITERAL = 0x01,
	TOK_PIPE = 0x08,
	TOK_VAR = 0x10,
	TOK_DBLQ = 0x20,
	TOK_SNGQ = 0x40,
	TOK_HRDC = 0x80,
	TOK_FILEIN = 0x100,
	TOK_FILEOUT = 0x200,
	TOK_FILEAPND = 0x400,
};

typedef struct token
{
	char				*raw;
	char				*token;
	char				**subtokens;
	int					type;
	bool				space_after;
	int					len;
	struct token		*next;
	struct token		*prev;
}	t_token;

#endif