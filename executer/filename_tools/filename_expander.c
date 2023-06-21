/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 15:34:59 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/21 12:40:58 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../env_tools/env_manager.h"
#include "../../libft/libft.h"

// defined in ./filename_velidator.c
int		validate_filename(char	*fname);
// defined in parser/tokenizers/token_expanders.c
size_t	env_namelen(char *name);

void	filename_errexit(char	*fname, char *err)
{
	ft_printf_fd(2, "minishell: %s: %s\n", fname, err);
	exit (1);
}


int	aux_expander(char **ftoken, char	*fname, int fname_len)
{
	char	*vname;
	char	*vval;

	vname = ft_substr(*ftoken, 1, env_namelen(*ftoken + 1));
	vval = env_lookup(vname);
	if (!vval)
		vval = "";
	ft_strlcat(fname, vval, fname_len);
	*ftoken += ft_strlen(vname) + 1;
	free(vname);
	return (ft_strlen(vval));
}

char	*expand_fname(char	*ftoken, int fname_len)
{
	char	*fname;
	int		fln;
	char	qt;

	fln = 0;
	fname = ft_calloc(fname_len + 1, sizeof(char));
	while (*ftoken)
	{
		if (ft_strchr("\"'", *ftoken) && !qt)
			qt = *(ftoken++);
		else if (*ftoken == qt && ftoken++)
			qt = 0;
		else if (*ftoken == '$' && env_namelen(ftoken + 1) && qt != '\'')
			fln += aux_expander(&ftoken, fname, fname_len);
		else
			fname[fln++] = *(ftoken++);
	}
	return (fname);
}

/// @brief expand filename from merged tokens and throw error if ambiguous 
char	*filename_expand(char	*ftoken)
{
	int		fname_len;

	fname_len = validate_filename(ftoken);
	if (fname_len == -1)
		filename_errexit(ftoken, "ambiguous redirect");
	else if (fname_len == 0)
		filename_errexit("", "No such file or directory");
	return (expand_fname(ftoken, fname_len));
}
