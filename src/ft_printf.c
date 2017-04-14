/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:56:39 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 19:13:20 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_conv(t_flags *flag, t_data *data, t_format *str)
{
	if (flag->conv_i >= 0 && flag->conv_i <= 8)
		ft_putstr_pf(ft_make_num(flag, data->nb), &str->cnt);
	else if (flag->conv_i == 9 && flag->lm == 0)
		ft_putstr_pf(ft_make_c(flag, data->c, &str->cnt), &str->cnt);
	else if ((flag->conv_i == 10) ||
		(flag->conv_i == 9 && flag->lm == 3))
		ft_putwstr_pf(ft_make_wc(flag, data->w_chr, &str->cnt), &str->cnt);
	else if (flag->conv_i == 11 && flag->lm == 0)
	{
		// ft_putendl("regular");
		ft_putstr_pf(ft_make_s(flag, data->str), &str->cnt);
	}
	else if ((flag->conv_i == 12) || (flag->conv_i == 11 && flag->lm == 3))
		ft_putwstr_pf(ft_make_wstr(flag, data->w_str), &str->cnt);
	else if (flag->conv_i == 13)
		ft_putstr_pf(ft_make_ptr(data->ptr), &str->cnt);
	else if (flag->conv_i == 14)
		ft_putstr_pf(ft_make_c(flag, data->c, &str->cnt), &str->cnt);
}

void	ft_get_wp(t_flags *flag, va_list *arg)
{
	if (flag->fw_ast)
	{
		flag->f_width = va_arg(*arg, int);
		flag->fw_ast = 0;
	}
	if (flag->p_ast)
	{
		flag->precision = va_arg(*arg, int);
		flag->p_ast = 0;
	}
}

void	ft_conversion(va_list *arg, t_flags *flag, t_data *data, t_format *str)
{
	str->found = str->tmp;
	str->tmp++;
	if ((ft_clen(str->tmp) == -1))
	{
		str->tmp--;
		return ;
	}
	str->conv = (char *)malloc(sizeof(char) * ft_clen(str->tmp) + 1);
	str->conv = ft_strncpy(str->conv, str->tmp, ft_clen(str->tmp));
	str->conv[ft_clen(str->tmp)] = '\0';
	if ((ft_parse(str->conv, flag)) == -1)
		return ;
	if (flag->fw_ast || flag->p_ast)
		ft_get_wp(flag, arg);
	ft_getdata(flag, arg, data);
	ft_print_conv(flag, data, str);
	str->tmp += (ft_clen(str->tmp) - 1);
	free(str->conv);
	str->conv = NULL;
}

int		ft_printf(const char *restrict format, ...)
{
	va_list		arg;
	t_flags		flag;
	t_data		data;
	t_format	str;

	va_start(arg, format);
	ft_bzero(&str, sizeof(t_format));
	ft_bzero(&flag, sizeof(t_flags));
	ft_bzero(&data, sizeof(t_data));
	str.tmp = (char *)format;
	while (*str.tmp)
	{
		if (*str.tmp != '%')
			ft_putchar_pf(*str.tmp, &str.cnt);
		else
		{
			ft_conversion(&arg, &flag, &data, &str);
			ft_bzero(&flag, sizeof(t_flags));
			ft_bzero(&data, sizeof(t_data));
		}
		str.tmp++;
	}
	va_end(arg);
	return (str.cnt);
}
