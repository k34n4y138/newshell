/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:32:48 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/09 21:43:14 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "command_builders/t_command.h"

t_command	*parse_command(char *line);
void		destroy_commands(t_command *command);
#endif
