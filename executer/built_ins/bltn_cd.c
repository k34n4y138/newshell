/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:48:32 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/21 20:07:26 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>
#include "../../libft/libft.h"

char	*get_env_path(char	*name, int redir)
{
	char	*path;

	path = env_lookup(name);
	if (!name)
	{
		ft_printf_fd(2, "cd: %s not set\n", name);
		if (redir & (REDIR_PIPEIN | REDIR_PIPEOUT))
			exit(1);
		env_exit_status(1, 1);
	}
	return (path);
}

void	bltn_cd(t_command *cmd)
{
	char	*where_togo;
	char	*tmpwd;

	if (cmd->argc < 2 || !ft_strcmp(cmd->argv[1], "~"))
		where_togo = get_env_path("HOME", cmd->redirs);
	else if (!ft_strcmp(cmd->argv[1], "-"))
		where_togo = get_env_path("OLDPWD", cmd->redirs);
	else
		where_togo = cmd->argv[1];
	tmpwd = getcwd(NULL, 0);
	if (chdir(where_togo) == -1)
	{
		perror("cd");
		if (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT))
			exit(1);
		env_exit_status(1, 1);
	}
	env_set("OLDPWD", tmpwd);
	free(tmpwd);
	tmpwd = getcwd(NULL, 0);
	env_set("PWD", tmpwd);
	free(tmpwd);
	if (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT))
		exit(0);
	env_exit_status(0, 1);
}
