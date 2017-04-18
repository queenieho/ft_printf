/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getdata.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:40:47 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 15:39:08 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** ********************************* **
**    Collecting data from va_arg    **
** ********************************* **
*/

void	ft_negnum(t_flags *flag, t_data *data)
{
	flag->plus = 1;
	flag->neg = 1;
	data->nb = -data->nb;
}

void	ft_getshrtlong(t_flags *flag, va_list *arg, t_data *data)
{
	if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 1)
	{
		data->nb = (char)va_arg(*arg, int);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = UCHAR_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 2)
	{
		data->nb = (short)va_arg(*arg, int);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = USHRT_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 6 && flag->conv_i <= 8) ||
		((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 3))
	{
		data->nb = va_arg(*arg, long);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = ULONG_MAX + data->nb + 1;
	}
	if (data->nb < 0 &&
		((flag->conv_i == 0 || flag->conv_i == 1 || flag->conv_i == 6)))
		ft_negnum(flag, data);
}

void	ft_getllong(t_flags *flag, va_list *arg, t_data *data)
{
	if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 4)
	{
		data->nb = va_arg(*arg, long long);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = ULLONG_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 5)
	{
		data->nb = va_arg(*arg, intmax_t);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = SIZE_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 6)
	{
		data->nb = va_arg(*arg, size_t);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = SIZE_MAX + data->nb + 1;
	}
	if (data->nb < 0 &&
		((flag->conv_i == 0 || flag->conv_i == 1 || flag->conv_i == 6)))
		ft_negnum(flag, data);
}

void	ft_getnumber(t_flags *flag, va_list *arg, t_data *data)
{
	if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 0)
	{
		data->nb = va_arg(*arg, int);
		if (data->nb < 0 && (flag->conv == 'd' || flag->conv == 'D' ||
			flag->conv == 'i'))
			ft_negnum(flag, data);
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = UINT_MAX + data->nb + 1;
	}
	else if (((flag->conv_i >= 0 && flag->conv_i <= 5) && (flag->lm >= 1 &&
		flag->lm <= 3)) || (flag->conv_i >= 6 && flag->conv_i <= 8))
		ft_getshrtlong(flag, arg, data);
	else if (flag->lm >= 4 && flag->lm <= 6)
		ft_getllong(flag, arg, data);
}

void	ft_getdata(t_flags *flag, va_list *arg, t_data *data)
{
	if (flag->conv_i >= 0 && flag->conv_i <= 8)
		ft_getnumber(flag, arg, data);
	else if (flag->conv_i == 9 && flag->lm == 0)
		data->c = va_arg(*arg, int);
	else if ((flag->conv_i == 10) ||
		(flag->conv_i == 9 && flag->lm == 3))
		data->w_chr = va_arg(*arg, wchar_t);
	else if (flag->conv_i == 11 && flag->lm == 0)
		data->str = va_arg(*arg, char*);
	else if ((flag->conv_i == 12) ||
		(flag->conv_i == 11 && flag->lm == 3))
		data->w_str = va_arg(*arg, wchar_t*);
	else if (flag->conv_i == 13)
		data->ptr = va_arg(*arg, void*);
	else
		data->c = '%';
}
