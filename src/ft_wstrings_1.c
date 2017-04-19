/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrings_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:54:10 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 19:10:38 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Applying width to w_char
*/

void	ft_mod_wstr(wchar_t **str)
{
	wchar_t *tmp;

	tmp = *str;
	while (*tmp)
	{
		if (*tmp == ' ')
			*tmp = '0';
		tmp++;
	}
}

int		ft_wchar_len(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else
		return (4);
}

int		ft_wstr_len(const wchar_t *ws)
{
	unsigned int i;

	i = 0;
	while (*ws)
	{
		i += (ft_wchar_len(*ws));
		ws++;
	}
	return (i);
}
