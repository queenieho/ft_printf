/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_wstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:59:49 by qho               #+#    #+#             */
/*   Updated: 2017/04/16 17:14:07 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_samewidth_ws(wchar_t *ret, wchar_t *str, int width, int left)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (left)
	{
		while (str[j])
			ret[i++] = str[j++];
		while (i < width + j - ft_wstr_len(str))
			ret[i++] = ' ';
		ret[i] = '\0';
	}
	else
	{
		while (i < (width - ft_wstr_len(str)))
			ret[i++] = ' ';
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
}

wchar_t	*ft_makewide_ws(wchar_t *str, int width, int left)
{
	wchar_t	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (width > ft_wstr_len(str))
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
		ft_samewidth_ws(ret, str, width, left);
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstr_len(str) + 1));
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	return (ret);
}

wchar_t	*ft_make_wc(t_flags *flag, int c, t_format *str)
{
	wchar_t	*ret;
	// int		n_cnt;

	// n_cnt = 0;
	ft_checkflags(flag, 0);
	if (c)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 2);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 1);
		ret[0] = '\0';
		(void)str;
		if (flag->f_width)
			flag->f_width--;
		// n_cnt = 1;
	}
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width, flag->minus);
	// str->cnt += n_cnt;
	return (ret);
}

/*
** Making wstring from wstring!
*/

wchar_t	*ft_makepres_ws(wchar_t *str, t_flags *flag)
{
	wchar_t	*ret;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (flag->x_pres)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 1);
		ret[0] = '\0';
	}
	if (flag->precision < ft_wstr_len(str))
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (flag->precision + 1));
		while (str[++i] && len < flag->precision)
		{
			ret[i] = str[i];
			len += ft_wchar_len(ret[i]);
			if (len > flag->precision)
				break ;
		}
		ret[i] = '\0';
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstr_len(str) + 1));
		while (str[++i])
			ret[i] = str[i];
		ret[i] = '\0';
	}
	return (ret);
}

wchar_t	*ft_make_wstr(t_flags *flag, wchar_t *str)
{
	// ft_putendl("whyyyyy");
	wchar_t *ret;

	if (!str)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 7);
		ret = L"(null)";
		// ft_putwstr(ret);
		return (ret);
	}
	else
		ret = str;
	ft_checkflags(flag, 0);
	if (flag->precision || flag->x_pres)
		ret = ft_makepres_ws(ret, flag);
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width, flag->minus);
	if (flag->zero)
		ft_mod_wstr(&ret);
	return (ret);
}
