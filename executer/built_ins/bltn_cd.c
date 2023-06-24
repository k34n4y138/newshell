/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bltn_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:48:32 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/23 22:19:17 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <unistd.h>
#include "../../libft/libft.h"

void	aux_exit(int redir, int ret)
{
	if (redir & (REDIR_PIPEIN | REDIR_PIPEOUT))
		exit(ret);
	env_exit_status(ret, 1);
}

char	*get_env_path(char	*name, int redir)
{
	char	*path;

	path = env_lookup(name);
	if (!path)
	{
		ft_printf_fd(2, "minishell: cd: %s not set\n", name);
		aux_exit(redir, 1);
	}
	return (path);
}

void	set_pwd(char *path, int redir)
{
	char	*tmpwd;
	int		err;

	err = 0;
	tmpwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		err = 1;
	}
	if (!err)
		env_update("OLDPWD", tmpwd, 1);
	free(tmpwd);
	tmpwd = getcwd(NULL, 0);
	if (!err)
		env_update("PWD", tmpwd, 1);
	free(tmpwd);
	aux_exit(redir, err);
}

void	bltn_cd(t_command *cmd)
{
	char	*where_togo;

	if (cmd->argc < 2 || !ft_strcmp(cmd->argv[1], "~"))
		where_togo = get_env_path("HOME", cmd->redirs);
	else if (!ft_strcmp(cmd->argv[1], "-"))
	{
		where_togo = get_env_path("OLDPWD", cmd->redirs);
		if (!where_togo)
			return ;
		write(1, where_togo, ft_strlen(where_togo));
		write(1, "\n", 1);
	}
	else
		where_togo = cmd->argv[1];
	if (!where_togo)
		return ;
	set_pwd(where_togo, cmd->redirs);
}
