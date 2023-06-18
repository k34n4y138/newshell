/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 23:32:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/18 02:18:53 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../parser/command_builders/t_command.h"

int	bltn_export(t_command *cmd);
int	bltn_unset(t_command *cmd);
int	bltn_env(t_command *cmd);
#endif