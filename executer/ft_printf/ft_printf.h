/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowazga <yowazga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:12:34 by yowazga           #+#    #+#             */
/*   Updated: 2023/05/22 15:32:58 by yowazga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<unistd.h>
# include<stdarg.h>

void	ft_putchar(int c, int *count);
void	ft_putstr(char *str, int *count);
void	ft_puthex(unsigned long long nb, char c, int *count);
void	ft_putadd(void *adr, int *count);
void	ft_putnbr(long nb, int *count);
int		ft_printf(const char *str, ...);

#endif
