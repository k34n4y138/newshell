/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:18:16 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/08 20:18:03 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H
# include <stdbool.h>
# include "../env_tools/env_manager.h"

enum	e_redirection
{
	REDIR_NONE = 0x0,
	//
	REDIR_FILEIN = 0x08,
	REDIR_PIPEIN = 0x10,
	REDIR_HEREDOC = 0x20,
	//
	REDIR_FILEOUT = 0x40,
	REDIR_FILEAPND = 0x80,
	REDIR_PIPEOUT = 0x100,
};

typedef struct redirect
{
	int				type;
	char			*file;
	int				fd;
	struct redirect	*next;
	struct redirect	*prev;
}	t_redirection;

enum	e_tokens
{
	TOK_LITERAL,
	TOK_PIPE,
	TOK_VAR,
	TOK_DBLQ,
	TOK_SNGQ,
	TOK_HRDC,
	TOK_FILEIN,
	TOK_FILEOUT,
	TOK_FILEAPND,
};


typedef	struct token
{
	char				*raw;
	char				*token;
	int					type;
	bool				space_after;
	size_t				len;
	struct token		*next;
	struct token		*prev;
}	t_token;


enum 
{
	IO_IN;
	IO_OUT;
}


typedef	struct command
{
	char				*rawline;
	t_token				*tokens;
	char				*command;
	char				**args;
	int					redirections;
	int					io[2];
	t_redirection		*redirects;
	struct command		*next;
	struct command		*prev;
}	t_command;


t_command *parse_commandline(char *line);
#endif
