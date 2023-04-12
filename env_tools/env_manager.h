/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:55 by zmoumen           #+#    #+#             */
/*   Updated: 2023/04/11 18:19:50 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H
# include "../libft/libft.h"


char	***env_store(int destroy);
char	**env_init(char **initenv);
char	*env_lookup(char *key);
int		env_insert(char *key, char *value);
int		env_update(char *key, char *value);
int		env_delete(char *key);
#endif