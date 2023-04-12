/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:25:08 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/30 11:31:59 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	bfr_or_read_fresh(int fd, char *remaining_bfr, char *reading_bfr)
{
	if (read(fd, NULL, 0) == -1)
		return (-1);
	if (ft_strlen(remaining_bfr))
		return (ft_strlcat(reading_bfr, remaining_bfr, BUFFER_SIZE + 1));
	else
		return (read(fd, reading_bfr, BUFFER_SIZE));
}

int	get_nl_indx(char *s)
{
	int	idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

char	*realloc_n_join(char *reading_bfr, char *ptr, int copy_till)
{
	char	*new_ptr;
	int		alloc_sz;

	alloc_sz = copy_till;
	if (ptr)
		alloc_sz += ft_strlen(ptr);
	alloc_sz++;
	new_ptr = ft_calloc(alloc_sz, sizeof(char));
	if (ptr)
	{
		ft_strlcat(new_ptr, ptr, alloc_sz);
		free(ptr);
	}
	ft_strlcat(new_ptr, reading_bfr, alloc_sz);
	return (new_ptr);
}

int	locate_nl_n_break(char *reading_bfr, int bytes_read,
		char *remaining_bfr, char **ptr)
{
	int	nl_idx;

	nl_idx = get_nl_indx(reading_bfr);
	if (nl_idx == -1)
	{		
		*ptr = realloc_n_join(reading_bfr, *ptr, bytes_read);
		return (0);
	}
	else
	{
		*ptr = realloc_n_join(reading_bfr, *ptr, nl_idx + 1);
		ft_bzero(remaining_bfr, BUFFER_SIZE +1);
		ft_strlcat(remaining_bfr, reading_bfr + nl_idx + 1, BUFFER_SIZE + 1);
		return (1);
	}
}

char	*get_next_line(int fd)
{
	static char	remaining_bfr[BUFFER_SIZE + 1] = "";
	char		reading_bfr[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*ptr;

	bytes_read = 0;
	ptr = 0;
	ft_bzero(reading_bfr, BUFFER_SIZE +1);
	while (fd >= 0)
	{
		bytes_read = bfr_or_read_fresh(fd, remaining_bfr, reading_bfr);
		ft_bzero(remaining_bfr, BUFFER_SIZE + 1);
		if (bytes_read <= 0)
			break ;
		reading_bfr[bytes_read] = 0;
		if (locate_nl_n_break(reading_bfr, bytes_read, remaining_bfr, &ptr))
			break ;
	}
	if (bytes_read == -1 && ptr)
	{
		free(ptr);
		return (0);
	}
	return (ptr);
}
