/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:18:16 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/12 22:49:18 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H
# include <stdbool.h>
# include "../env_tools/env_manager.h"

enum	e_redirection
{
	REDIR_NONE = 0x0,
	
	REDIR_FILEIN  = 8,
	REDIR_PIPEIN = 64,
	REDIR_HEREDOC = 256,
	
	REDIR_FILEOUT = 16,
	REDIR_FILEAPND = 32,
	REDIR_PIPEOUT = 128,
	
};


typedef struct redirect
{
	int		type;
	char	*file;
	int		fd;
	struct redirect	*next;
	struct redirect	*prev;
}	t_redirect;


typedef struct s_task
{
	char	*command;
	char	**args;
	
	int		redirections;
	int		fd_in;
	int		fd_out;
	
	struct s_task	*next;
	struct s_task	*prev;
	
}


#endif
