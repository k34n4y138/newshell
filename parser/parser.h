/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:32:48 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/20 15:44:32 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "command_builders/t_command.h"

t_command	*parse_command(char *line);
void		destroy_commands(t_command *command);
#endif
