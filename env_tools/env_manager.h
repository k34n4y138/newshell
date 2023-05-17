/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:55 by zmoumen           #+#    #+#             */
/*   Updated: 2023/05/16 20:38:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H

/// @brief internal function to store the environment
char	***env_store(int destroy);

/// @brief initialize the environment
char	**env_init(char **initenv);

/// @brief destroy the environment
void	env_destroy(void);

/// @brief returns the value of the key if it exists, NULL otherwise
char	*env_lookup(char *key);

/// @brief insert a new key=value pair to the env
int		env_insert(char *key, char *value);

/// @brief update the value of the key if it exists, insert it otherwise
int		env_update(char *key, char *value);

/// @brief Delete the key=value pair from the env
/// @return 0 if the key exists, 1 otherwise
int		env_delete(char *key);
#endif