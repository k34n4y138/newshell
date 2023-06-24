/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:51:55 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/24 15:02:24 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_MANAGER_H
# define ENV_MANAGER_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_envirun;

/// @brief internal function to store the environment
t_envirun	**env_store(int destroy);

/// @brief initialize the environment
void		env_init(char **initenv);

/// @brief returns the value of the key if it exists, NULL otherwise
char		*env_lookup(char *key);

/// @brief insert a new key=value pair to the env
int			env_insert(char *key, char *value);

/// @brief update the value of the key if it exists, insert it otherwise
int			env_update(char *key, char *value, int create);

/// @brief Delete the key=value pair from the env
/// @return 0 if the key exists, 1 otherwise
int			env_delete(char *key);

/// @brief returns the exit status of the last command
int			env_exit_status(int status, int set);

/// @brief returns the environment as a char **
char		**env_export(void);

/// @brief check if the key is valid
int			env_validate_key(char *key);
#endif