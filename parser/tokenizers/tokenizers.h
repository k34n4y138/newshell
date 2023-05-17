/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:38:41 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/17 20:31:37 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TOKENIZERS_H
# define TOKENIZERS_H
# include "t_token.h"


t_token	*tokenizer(char	*line);

void	tokens_expander(t_token	*token);
#endif