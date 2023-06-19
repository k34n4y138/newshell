/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:22:38 by yowazga           #+#    #+#             */
/*   Updated: 2023/06/19 22:54:01 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include "../parser/command_builders/t_command.h"
# include "../env_tools/env_manager.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

//define

# define READ_END 0
# define WRITE_END 1

//execition

void	exicution(t_command *cmds);
char	*get_path(char *path, char *cmd0, int status);
void	exit_file(char *file_name);

// utiles_get_path

void	check_cmd(t_command *cmd);
void	close_prev_pip(t_command *cmd);
void	dup_herdoc(t_command *cmd);
char	*ft_strnstr_1(char *str, char *to_find, int len);

//input_redires

void	handl_input(t_command *cmd);

//output_redires

void	handl_output(t_command *cmd);
void	read_lin(t_redirection *redirect);

#endif