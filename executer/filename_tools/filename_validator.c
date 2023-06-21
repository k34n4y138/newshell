/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:33:20 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/21 12:41:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"
#include "stdlib.h"

// defined in parser/tokenizers/token_expanders.c
size_t	env_namelen(char *name);

int	aux_qtcheck(char c, char *quote_found, int *expanded)
{
	if (!*quote_found && (c == '\'' || c == '"'))
	{
		*expanded |= 0x02;
		*quote_found = c;
		return (1);
	}
	else if (*quote_found == c)
	{
		*quote_found = 0;
		return (1);
	}
	return (0);
}

int	check_ambiguous(char	**fname, char qt, int	*namelen, int	*expanded)
{
	char	*vname;
	char	*vval;

	*expanded |= 0x01;
	vname = ft_substr(*fname, 1, env_namelen(*fname + 1));
	vval = env_lookup(vname);
	if (!vval)
		vval = "";
	free(vname);
	if (!qt && (ft_strchr(vval, ' ') || ft_strchr(vval, '\t')))
		return (-1);
	*fname += env_namelen(*fname + 1) + 1;
	*namelen += ft_strlen(vval);
	return (0);
}

int	validate_filename(char	*fname)
{
	char	qt;
	int		fname_len;
	int		expanded;

	qt = 0;
	fname_len = 0;
	expanded = 0;
	while (*fname)
	{
		if (aux_qtcheck(*fname, &qt, &expanded))
			fname++;
		else if (*fname == '$' && env_namelen(fname + 1) && qt != '\'')
		{
			if (check_ambiguous(&fname, qt, &fname_len, &expanded))
				return (-1);
		}
		else
		{
			fname_len++;
			fname++;
		}
	}
	if (expanded == 1 && fname_len == 0)
		return (-1);
	return (fname_len);
}
