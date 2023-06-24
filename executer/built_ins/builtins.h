/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:32:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/24 10:59:43 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../execution.h"
# include "../../parser/command_builders/t_command.h"

# define EXIT_WITH_PIP 1
# define SINGL_EXIT 0

void	bltn_export(t_command *cmd);
int		bltn_unset(t_command *cmd);
void	bltn_env(t_command *cmd);
void	bltn_pwd(t_command *cmd);
void	bltn_exit(t_command *cmd, int key);
void	bltn_echo(t_command *cmd);
void	bltn_cd(t_command *cmd);

#endif