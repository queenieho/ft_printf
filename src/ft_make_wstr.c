/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_wstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:59:49 by qho               #+#    #+#             */
/*   Updated: 2017/04/20 10:04:21 by qho              ###   ########.fr       */
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
	}
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width, flag->minus);
	return (ret);
}

wchar_t	*ft_make_wstr(t_flags *flag, wchar_t *str)
{
	wchar_t *ret;

	if (!str)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 7);
		ret = L"(null)";
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

void	ft_print_wchar(t_flags *flag, t_data *data, t_format *str)
{
	wchar_t	*w_print;

	w_print = NULL;
	if (data->w_chr == '\0' && flag->minus)
		ft_putwchar_pf('\0', &str->cnt);
	w_print = ft_make_wc(flag, data->w_chr, str);
	ft_putwstr_pf(w_print, &str->cnt);
	if (data->w_chr == '\0' && !flag->minus)
		ft_putwchar_pf('\0', &str->cnt);
	if (w_print)
		free(w_print);
}
