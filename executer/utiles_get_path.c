/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_get_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:14:26 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 18:18:45 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"

void	close_prev_pip(t_command *cmd)
{
	if (cmd->next != NULL && (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT)))
	{
		close(cmd->pip[WRITE_END]);
		if (cmd->prev != NULL)
			close(cmd->prev->pip[READ_END]);
	}
}

void	dup_herdoc(t_command *cmd)
{
	int	fd;

	fd = open(".stor_herdoc", O_RDONLY, 0644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
}

char	*ft_strnstr_1(char *str, char *to_find, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[i] == '\0' && to_find[i] == '\0')
		return (str);
	while (str[i] && j + i < len)
	{
		while (str[i] == to_find[i] && j + i < len)
		{
			i++;
			if (to_find[i] == '\0')
			{
				if (ft_strlen(str) == ft_strlen(to_find))
					return (str);
			}
		}
		str++;
		i = 0;
		j++;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i])
	{
		while (str[i] == to_find[i])
		{
			i++;
			if (to_find[i] == '\0')
				return (str);
		}
		str++;
		i = 0;
	}
	return (0);
}

void	check_cmd(t_command *cmd)
{
	if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.'
		|| (ft_strstr(cmd->argv[0], ".sh") && ft_strchr(cmd->argv[0], 47)))
	{
		if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
			cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 1);
		else
			cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
	}
	else
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
}
