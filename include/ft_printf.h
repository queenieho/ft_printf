/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:52:29 by qho               #+#    #+#             */
/*   Updated: 2017/04/04 14:28:56 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BASE "0123456789ABCDEF"


#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <wchar.h>

void	ft_memdel(void **ap);
void	ft_strdel(char **as);
char	*ft_itoa_base(long value, int base);
void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putnbr(long nb);
int		ft_strlen(const char *s);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_changecase(char *str);
int		ft_tolower(int c);
int		ft_printf(const char * restrict format, ...);

#endif
