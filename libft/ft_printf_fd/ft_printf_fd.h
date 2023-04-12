/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoumen <zmoumen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:41:56 by zmoumen           #+#    #+#             */
/*   Updated: 2023/01/30 11:49:03 by zmoumen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H
# include <stdarg.h>

int		ft_printf_fd(int fd, const char *str, ...);
char	*ctoa(int c);
char	*ft_ultoa_base(unsigned long nb, char *base, char *prefix);

#endif 