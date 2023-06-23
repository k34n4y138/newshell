#include "execution.h"

char	*expand_line(char *line);

t_redirection	*check_last_input_herdoc(t_command *cmd)
{
	t_redirection	*last_infile;
	t_redirection	*redirect;

	redirect = cmd->_redirects;
	while (redirect)
	{
		if (redirect->type & REDIR_HEREDOC)
			last_infile = redirect;
		redirect = redirect->next;
	}
	return (last_infile);
}

void		start_read_herdoc(t_redirection *redirect, int *pip)
{
	t_herdoc hed;

	hed.stor = ft_calloc(1, 1);
	close(pip[0]);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		hed.read_2 = readline("> ");
		if (!(redirect->type & REDIR_HEREDOC) && hed.read_2)
		{
			hed.read = expand_line(hed.read_2);
			free(hed.read_2);
		}
		else
			hed.read = hed.read_2;
		if (!hed.read || !ft_strcmp(redirect->file, hed.read))
		{
			free(hed.read);
			break ;
		}
		hed.stor = ft_strjoin_free(hed.stor, hed.read, 1, 1);
		hed.stor = ft_strjoin_free(hed.stor, "\n", 1, 0);
	}
	write(pip[1], hed.stor, ft_strlen(hed.stor));
	close(pip[1]);
	exit(0);
}

void read_herdoc(t_command *cmd)
{
	t_command		*head;
	t_redirection	*redirect;
	pid_t			pid;
	int				pip[2];

	head = cmd;
	while (head && (head->redirs & REDIR_HEREDOC))
	{
		redirect = head->_redirects;
		while (redirect && (redirect->type & REDIR_HEREDOC))
		{
			if (pipe(pip) == -1)
				exit(EXIT_FAILURE);
			pid = fork();
			if (pid == -1)
				exit(EXIT_FAILURE);
			else if (pid == 0)
				start_read_herdoc(redirect, pip);
			waitpid(pid, NULL, 0);
			redirect->fd = pip[0];
			close(pip[1]);
			redirect = redirect->next;
		}
		head = head->next;
	}
}