/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:40:29 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 18:25:07 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_pf(char c, int *cnt)
{
	write(1, &c, 1);
	*cnt += 1;
}

void	ft_putstr_pf(char const *s, int *cnt)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_pf(s[i], cnt);
			i++;
		}
	}
}

void	ft_putwchar_pf(wchar_t c, int *cnt)
{
	if (c <= 0x7F)
		ft_putchar_pf(c, cnt);
	else if (c <= 0x7FF)
	{
		ft_putchar_pf(0xC0 | (c >> 6), cnt);
		ft_putchar_pf(0x80 | (c & 0x3F), cnt);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_pf(0xE0 | (c >> 12), cnt);
		ft_putchar_pf(0x80 | ((c >> 6) & 0x3F), cnt);
		ft_putchar_pf(0x80 | (c & 0x3F), cnt);
	}
	else if (c <= 0x1FFFF)
	{
		ft_putchar_pf(0xF0 | (c >> 18), cnt);
		ft_putchar_pf(0x80 | ((c >> 12) & 0x3F), cnt);
		ft_putchar_pf(0x80 | ((c >> 6) & 0x3F), cnt);
		ft_putchar_pf(0x80 | (c & 0x3F), cnt);
	}
}

void	ft_putwstr_pf(wchar_t *str, int *cnt)
{
	while (*str)
		ft_putwchar_pf(*str++, cnt);
}
