/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_wstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:59:49 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 19:20:51 by qho              ###   ########.fr       */
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
		while (i < width)
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

wchar_t	*ft_make_wc(t_flags *flag, int c, int *cnt)
{
	wchar_t	*ret;
	int		n_cnt;

	n_cnt = 0;
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
		n_cnt = 1;
	}
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width - n_cnt, flag->minus);
	*cnt += n_cnt;
	return (ret);
}

/*
** Making wstring from wstring!
*/

wchar_t	*ft_makepres_ws(wchar_t *str, int pres)
{
	wchar_t	*ret;
	int		i;
	int		len;

	i = -1;
	len = 0;
	if (pres < ft_wstr_len(str))
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (pres + 1));
		while (str[++i] && len < pres)
		{
			ret[i] = str[i];
			len += ft_wchar_len(ret[i]);
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

	// (void)str;
	// (void)flag;
	// ret = (wchar_t *)malloc(sizeof(wchar_t) * 2);
	// ret[0] = 'H';
	// ret[1] = '\0';

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
	if (flag->precision)
		ret = ft_makepres_ws(ret, flag->precision);
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width, flag->minus);
	return (ret);
}
