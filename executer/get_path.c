/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:20:53 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 22:58:54 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	print_error(char *msg, char *cmd)
{
	ft_printf_fd(2, "minishell: %s: %s\n", cmd, msg);
	exit(127);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*check_p(char *cmd)
{
	char	*valid;

	valid = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			valid = ft_strdup(cmd);
		else
		{
			ft_printf_fd(2, "minishell: permission denied: %s\n", cmd);
			exit (126);
		}
	}
	return (valid);
}

char	*get_valid_path(char *path, char *cmd0)
{
	char	**paths;
	char	*valid;
	int		i;

	i = -1;
	valid = NULL;
	paths = NULL;
	paths = ft_split(path, ':');
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], cmd0);
		if (access(paths[i], F_OK) == 0)
		{
			valid = ft_strdup(paths[i]);
			break ;
		}
	}
	free_paths(paths);
	return (valid);
}

char	*get_path(char *path, char *cmd0, int status)
{
	char	*valid_path;

	valid_path = NULL;
	if (!path)
		print_error("No such file or directory", cmd0);
	if (status == 0)
	{
		valid_path = get_valid_path(path, cmd0);
		if (!valid_path)
			print_error("command not found", cmd0);
	}
	else if (status == 1)
	{
		valid_path = check_p(cmd0);
		if (!valid_path)
			print_error("No such file or directory", cmd0);
	}
	return (valid_path);
}
