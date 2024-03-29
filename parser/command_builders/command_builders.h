/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builders.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:34:16 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/08 17:36:49 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_BUILDERS_H
# define COMMAND_BUILDERS_H
# include "../tokenizers/t_token.h"
# include "t_command.h"

t_command	*build_commandchain(t_token *tokens);
#endif