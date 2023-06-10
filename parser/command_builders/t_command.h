/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:56:35 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/10 15:33:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
# define T_COMMAND_H

/// @brief type mask for redirections
enum	e_redirection
{
	REDIR_NONE = 0x0,
	REDIR_HEREDOC = 0x80,
	REDIR_FILEIN = 0x100,
	REDIR_FILEOUT = 0x200,
	REDIR_FILEAPND = 0x400,
	REDIR_PIPEIN = 0x10,
	REDIR_PIPEOUT = 0x20,
};




/// @brief redirection structure
///		-# type: redirection type
///		-# file: file name or hrdc delimiter
///		-# fd: file descriptor
typedef struct redirect
{
	int				type;
	char			*file;
	int				fd;
	struct redirect	*next;
	struct redirect	*prev;
}	t_redirection;


/// @brief commandchain structure
///		-# argc: number of arguments
///		-# argv: array of arguments, the first argument is the command name
///		-# io: array of file descriptors,[0] is input and [1] is output
///		-# redirs: mask of redirections types
///		-# _redirects: linked list of redirections
typedef struct command
{
	int				argc;
	char			**argv;
	int				io[2];
	int				redirs;
	t_redirection	*_redirects;
	struct command	*next;
	struct command	*prev;
}	t_command;

#endif