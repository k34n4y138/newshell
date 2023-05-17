/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:56:35 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/16 20:08:07 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef T_COMMAND_H
# define T_COMMAND_H

enum	e_redirection
{
	REDIR_NONE = 0x0,
	REDIR_FILEIN = 0x08,
	REDIR_PIPEIN = 0x10,
	REDIR_HEREDOC = 0x20,
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

typedef struct comnand
{
	char			*command;
	char			**argc;
	char			**argv;
	int				io[2];
	t_redirection	*_redirects;
	struct command	*next;
	struct command	*prev;
}	t_command;

#endif