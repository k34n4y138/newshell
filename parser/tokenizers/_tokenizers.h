/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _tokenizers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:39:09 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/21 14:20:11 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _TOKENIZERS_H
# define _TOKENIZERS_H
# include "t_token.h"

int	split_redirection(char	*line, int toklen, t_token **tokens);
int	split_dollar(char	*line, t_token **tokens);
int	split_literal(char *line, t_token **tokens, bool subtok);
int	split_quote(char	*line, char qt, t_token **tokens);

#endif