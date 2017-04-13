/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrings_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:54:10 by qho               #+#    #+#             */
/*   Updated: 2017/04/12 14:55:24 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Applying width to w_char
*/

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
