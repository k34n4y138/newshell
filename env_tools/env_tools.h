/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:39:49 by zmoumen           #+#    #+#             */
/*   Updated: 2023/02/01 15:29:46 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOOLS_H
# define ENV_TOOSL_H
# include "../libft/libft.h"

typedef struct s_env
{
	char	*key;
	char	*val;
	int		exported;
}			t_env;
char	*expand_variable(char	*key);
#endif