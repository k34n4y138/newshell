/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exicution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:31:09 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 12:47:55 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exicution.h"
char    *expand_line(char *line);

void	exit_file(char *file_name)
{
	ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
	exit(1);
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

void	read_herdoc(t_command *cmd)
{
	t_redirection *redirect;
	char *read;
	
	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_HEREDOC)
		{
			redirect->fd = open(".stor_herdoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
			while (1)
			{
				read = readline("> ");
				if (!read || ft_strnstr_1(read, redirect->file, ft_strlen(redirect->file)))
				{
					free(read);
					break ;
				}
				ft_putstr_fd(read, redirect->fd);
				write(redirect->fd, "\n", 1);
				free(read);
			}
			close(redirect->fd);
		}
		redirect = redirect->next;
	}
}

t_redirection	*check_last_input_file(t_command *cmd)
{
	t_redirection *last_infile;
	t_redirection *redirect;
	
	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_FILEIN)
			last_infile = redirect;
		redirect = redirect->next;
	}
	return (last_infile);
}

int	which_last_input(t_command *cmd)
{
	int	last_in;
	t_redirection	*redirs;

	redirs = cmd->_redirects;
	while (redirs)
	{
		if (redirs->type & (REDIR_FILEIN | REDIR_HEREDOC))
			last_in = redirs->type;
		redirs = redirs->next;			
	}
	if (last_in & REDIR_FILEIN)
		return (REDIR_FILEIN);
	return (REDIR_HEREDOC);
}

void	dup_in_file(t_command *cmd)
{
	t_redirection *last_in_file;
	
	last_in_file = check_last_input_file(cmd);
	last_in_file->fd = open(last_in_file->file, O_RDONLY, 0644);
	if (last_in_file->fd == -1)
		exit_file(last_in_file->file);
	dup2(last_in_file->fd, STDIN_FILENO);
	close(last_in_file->fd);
	if (cmd->redirs & REDIR_PIPEIN)
		close(cmd->prev->pip[READ_END]);
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

void	check_infile(t_command *cmd)
{
	t_redirection *redirect;
	
	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_FILEIN)
		{
			redirect->fd = open(redirect->file, O_RDONLY, 0644);
			if (redirect->fd == -1)
				exit_file(redirect->file);
			close(redirect->fd);
		}
		redirect = redirect->next;
	}
}

void	handl_input(t_command *cmd)
{
	if (cmd->redirs & (REDIR_HEREDOC | REDIR_FILEIN))
	{
		if (cmd->redirs & REDIR_HEREDOC)
			read_herdoc(cmd);
		if (cmd->redirs & REDIR_FILEIN)
			check_infile(cmd);
		if (which_last_input(cmd) & REDIR_FILEIN)
			dup_in_file(cmd);
		else
			dup_herdoc(cmd);
	}
	else if (cmd->redirs & REDIR_PIPEIN)
	{
		dup2(cmd->prev->pip[READ_END], STDIN_FILENO);
		close(cmd->prev->pip[READ_END]);
	}
}

t_redirection	*creat_out_file(t_redirection *redirect)
{
	t_redirection *last_out;
	
	last_out = NULL;
	if (redirect->type & REDIR_FILEOUT)
	{
		redirect->fd = open(redirect->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		last_out = redirect;
		close(redirect->fd);
	}
	else if (redirect->type & REDIR_FILEAPND)
	{
		redirect->fd = open(redirect->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (redirect->fd == -1)
			exit_file(redirect->file);
		last_out = redirect;
		close(redirect->fd);
	}
	return (last_out);
}

void	handl_out_file(t_command *cmd, t_redirection *last_out)
{
	if (last_out->type & REDIR_FILEOUT)
	{
		last_out->fd = open(last_out->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (last_out->fd == -1)
			exit_file(last_out->file);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	else if (last_out->type & REDIR_FILEAPND)
	{
		last_out->fd = open(last_out->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (last_out->fd == -1)
			exit_file(last_out->file);
		dup2(last_out->fd, STDOUT_FILENO);
		close(last_out->fd);
	}
	if (cmd->redirs & REDIR_PIPEOUT)
		close(cmd->pip[WRITE_END]);
}

void	handl_output(t_command *cmd)
{
	t_redirection *last_out;
	t_redirection *redirect;
	
	redirect = cmd->_redirects;
	if (cmd->redirs & (REDIR_FILEOUT | REDIR_FILEAPND))
	{
		while (redirect)
		{
			if (redirect->type & REDIR_FILEIN)
			{
				if (access(redirect->file, F_OK) == -1)
					break ;
				redirect = redirect->next;
			}
			last_out = creat_out_file(redirect);
			redirect = redirect->next;
		}
		handl_out_file(cmd, last_out);
	}
	else if (cmd->redirs & REDIR_PIPEOUT)
	{
		dup2(cmd->pip[WRITE_END], STDOUT_FILENO);
		close(cmd->pip[WRITE_END]);
	}
}

int	is_empty(char *cmd)
{
	while (*cmd)
	{
		if (*cmd != 32 || *cmd != '\t')
			return (0);
		cmd++;
	}
	return (1);
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
		if (is_empty(cmd->argv[0]))
			ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		if (cmd->argv[0][0] == '/' || cmd->argv[0][0] == '.')
			cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 1);
		else
			cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
	}
	else
	{
		if (is_empty(cmd->argv[0]))
			ft_printf("minishell: %s: command not found\n", cmd->argv[0]);
		cmd->path = get_path(env_lookup("PATH"), cmd->argv[0], 0);
	}
}

void start_execution(t_command *cmd)
{
	handl_output(cmd);
	handl_input(cmd);
	check_cmd(cmd);
	cmd->envp = env_export();
	execve(cmd->path, cmd->argv, cmd->envp);
}

void	wait_for_childs(t_command *cmd)
{
	int	status;

	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		cmd->exit_status = status >> 8;
		cmd = cmd->next;
	}
}

void	close_prev_pip(t_command *cmd)
{
	if (cmd->next != NULL && (cmd->redirs & (REDIR_PIPEIN | REDIR_PIPEOUT)))
	{
		close(cmd->pip[WRITE_END]);
		if (cmd->prev != NULL)
			close(cmd->prev->pip[READ_END]);
	}
}

void	exicution(t_command *cmd)
{
	t_command	*head;

	head = cmd;
	while (cmd)
	{
		if (cmd->next != NULL)
		{
			if (pipe(cmd->pip) == -1)
			{
				perror("minishell");
				exit(EXIT_FAILURE);
			}
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (cmd->pid == 0)
			start_execution(cmd);
		close_prev_pip(cmd);
		// close(cmd->pip[WRITE_END]);
		cmd = cmd->next;
	}
	wait_for_childs(head);
}