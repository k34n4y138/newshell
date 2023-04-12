/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:38:51 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/12 15:39:11 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#include "env_tools/env_manager.h"

void	env_print(void)
{
	int		i;
	char	**env;

	i = 0;
	env = *env_store(0);
	while (env[i])
	{
		printf("%s\n",(env[i]));
		i++;
	}
}

int	main(int argc, char **argv, char **environ)
{
	char 	*line;
	char	*action;

	env_init(environ);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		char *ln = ft_strtok(line, " ");
		if (ft_strncmp(ln, "env", 3) == 0)
			env_print();
		else if (ft_strncmp(ln, "getenv",7) == 0)
		{
			action = ft_strtok(NULL, " ");
			printf(">>%s\n", env_lookup(action));
			free(action);
		}
		else if (ft_strncmp(ln, "export", 6) == 0)
		{
			action = ft_strtok(NULL, " ");
			char *value = ft_strtok(NULL, " ");
			printf("setting %s: %d\n", action, env_update(action, value));
			free(value);
			free(action);
		}
		else if (ft_strncmp(ln, "unset", 8) == 0)
		{
			action = ft_strtok(NULL, " ");
			printf("deleting %s: %d\n", action, env_delete(action));
			free(action);
		}
		else if (ft_strncmp(ln, "exit", 4) == 0)
			exit(0);
		else
			printf("command not found: %s\n", ln);
		free(ln);
		ln = ft_strtok(NULL, " ");
		while (ln)
		{
			printf("exess stuff>> %s\n",ln);
			free(ln);
			ln = ft_strtok(NULL, " ");
		}
		add_history(line);
		free(line);
	}
	return (0);
}
