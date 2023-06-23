/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:09:42 by zmoumen           #+#    #+#             */
/*   Updated: 2023/06/23 15:13:06 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include "../libft.h"
#define FLAGS "csdiuxX"

int	ft_buffer(char	*str, char c, int flush, int fd);

static char	*handle_hexa(const char *str, va_list valst)
{
	if (str[1] == 'X')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789ABCDEF", ""));
	if (str[1] == 'x')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789abcdef", ""));
	if (str[1] == 'p')
		return (ft_ultoa_base(va_arg(valst, unsigned long),
				"0123456789abcdef", "0x"));
	else if (str[1] == 'u')
		return (ft_ultoa_base(va_arg(valst, unsigned int),
				"0123456789", ""));
	return (0);
}

static void	aux_printnfree(char *strprint, int *len, char flg, int fd)
{
	if (!strprint)
		strprint = ft_strdup("(null)");
	ft_putstr_fd(strprint, fd);
	if (!ft_strlen(strprint) && flg == 'c')
	{
		ft_putchar_fd(0, fd);
		*len += 1;
	}
	else
		*len += ft_strlen(strprint);
	free(strprint);
}

static char	*aux_strdup(const char *s1)
{
	if (s1)
		return (ft_strdup(s1));
	return (NULL);
}

static int	handle_flags(const char *str, va_list valst, int *len, int fd)
{
	char	*strprint;
	int		jmplen;

	jmplen = 1;
	strprint = 0;
	if (str[0] == '%' && str[1])
	{
		if (ft_strchr("di", str[1]))
			strprint = ft_itoa(va_arg(valst, int));
		else if (ft_strchr("xXpu", str[1]))
			strprint = handle_hexa(str, valst);
		else if (str[1] == 's')
			strprint = aux_strdup(va_arg(valst, char *));
		else if (str[1] == 'c')
			strprint = ctoa(va_arg(valst, int));
		else
			strprint = ctoa(str[1]);
		jmplen = 2;
	}
	else
		strprint = ctoa(str[0]);
	aux_printnfree(strprint, len, str[1], fd);
	return (jmplen);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	valst;
	int		len;
	int		iter;

	len = 0;
	iter = 0;
	va_start(valst, str);
	while (str[iter])
	{
		if (str[iter] == '%' && str[1])
			iter += handle_flags(&str[iter], valst, &len, fd);
		else
		{
			ft_buffer(NULL, str[iter++], 0, fd);
			len++;
		}
	}
	ft_buffer(NULL, 0, 1, fd);
	return (len);
}
