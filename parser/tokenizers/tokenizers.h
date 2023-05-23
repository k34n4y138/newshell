/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:38:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/23 13:28:36 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TOKENIZERS_H
# define TOKENIZERS_H
# include "t_token.h"


t_token			*tokenizer(char *line, bool subtok);
void			expand_literal_tokens(t_token	*token);
int     		syntaxifier(t_token *tkn);
void        	merge_tokens(t_token	*tkn);
#endif