/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 11:20:53 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/22 17:04:06 by yowazga          ###   ########.fr       */
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

// char	*check_p(char *cmd)
// {
// 	char	*valid;

// 	valid = NULL;
// 	if (access(cmd, F_OK) == 0)
// 	{
// 		if (access(cmd, X_OK) == 0)
// 			valid = ft_strdup(cmd);
// 		else
// 		{
// 			ft_printf_fd(2, "minishell: %s: permission denied\n", cmd);
// 			exit (126);
// 		}
// 	}
// 	return (valid);
// }

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

char	*check_if_inpath(char *cmd)
{
	if (access(cmd, F_OK) == 0)	
		return (cmd);
	print_error("No such file or directory", cmd);
	return (NULL);
}

char	*get_path(char *path, char *cmd0, int status)
{
	char	*valid_path;

	valid_path = NULL;
	if (status == 1)
		return (cmd0);
	if (status == 0)
	{
		if (path && path[0] != '\0')
		{
			valid_path = get_valid_path(path, cmd0);
			if (!valid_path)
				print_error("command not found", cmd0);
		}
		else
			valid_path = check_if_inpath(cmd0);
		return (valid_path);
	}
	if (!path || path[0] == '\0')
		print_error("No such file or directory", cmd0);
	return (valid_path);
}
