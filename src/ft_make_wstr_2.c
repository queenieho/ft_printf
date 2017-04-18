/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_wstr_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 14:42:35 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 15:48:44 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Making wstring from wstring!
*/

wchar_t	*ft_makepres_ws02(wchar_t *str, t_flags *flag)
{
	wchar_t	*ret;
	int		i;
	int		len;

	i = -1;
	len = 0;
	ret = (wchar_t *)malloc(sizeof(wchar_t) * (flag->precision + 1));
	while (str[++i] && len < flag->precision)
	{
		ret[i] = str[i];
		len += ft_wchar_len(ret[i]);
		if (len > flag->precision)
			break ;
	}
	ret[i] = '\0';
	return (ret);
}

wchar_t	*ft_makepres_ws(wchar_t *str, t_flags *flag)
{
	wchar_t	*ret;
	int		i;

	i = -1;
	if (flag->x_pres)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 1);
		ret[0] = '\0';
	}
	if (flag->precision < ft_wstr_len(str))
		ret = ft_makepres_ws02(str, flag);
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstr_len(str) + 1));
		while (str[++i])
			ret[i] = str[i];
		ret[i] = '\0';
	}
	return (ret);
}
