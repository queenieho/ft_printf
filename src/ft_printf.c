/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:56:39 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 14:05:26 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_conv(t_flags *flag, t_data *data, t_format *str)
{
	if (flag->conv_i >= 0 && flag->conv_i <= 8)
		ft_putstr_pf(ft_make_num(flag, data->nb), &str->cnt);
	else if (flag->conv_i == 9 && flag->lm == 0)
	{
		if (data->c == '\0' && flag->minus)
			ft_putchar_pf('\0', &str->cnt);
		ft_putstr_pf(ft_make_c(flag, data->c, &str->cnt), &str->cnt);
		if (data->c == '\0' && !flag->minus)
			ft_putchar_pf('\0', &str->cnt);
	}
	else if ((flag->conv_i == 10) ||
		(flag->conv_i == 9 && flag->lm == 3))
	{
		if (data->w_chr == '\0' && flag->minus)
			ft_putwchar_pf('\0', &str->cnt);
		ft_putwstr_pf(ft_make_wc(flag, data->w_chr, str), &str->cnt);
		if (data->w_chr == '\0' && !flag->minus)
			ft_putwchar_pf('\0', &str->cnt);
	}
	else if (flag->conv_i == 11 && flag->lm == 0)
		ft_putstr_pf(ft_make_s(flag, data->str), &str->cnt);
	else if ((flag->conv_i == 12) || (flag->conv_i == 11 && flag->lm == 3))
		ft_putwstr_pf(ft_make_wstr(flag, data->w_str), &str->cnt);
	else if (flag->conv_i == 13)
		ft_putstr_pf(ft_make_ptr(flag, data->ptr), &str->cnt);
	else if (flag->conv_i == 14)
		ft_putstr_pf(ft_make_c(flag, data->c, &str->cnt), &str->cnt);
	else if (flag->conv_i == -1 && flag->conv != '\0')
		ft_putstr_pf(ft_make_c(flag, flag->conv, &str->cnt), &str->cnt);
}

void	ft_get_wp(t_flags *flag, va_list *arg)
{
	if (flag->fw_ast)
	{
		flag->f_width = va_arg(*arg, int);
		if (flag->f_width < 0)
		{
			flag->f_width = - flag->f_width;
			flag->minus = 1;
		}
		flag->fw_ast = 0;
	}
	if (flag->p_ast)
	{
		flag->precision = va_arg(*arg, int);
		if (flag->precision == 0)
			flag->x_pres = 1;
		else if (flag->precision < 0)
			flag->precision = 0;
		flag->p_ast = 0;
	}
}

int		ft_invalid(char *str)
{
	int i;
	// int j;

	i = 0;
	if (str[i])
	{
		while (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == '+' ||
			str[i] == ' ' || (str[i] >= '0' && str[i] <= '9') || str[i] == 'h' ||
			str[i] == '*' || str[i] == '.' || str[i] == 'l' || str[i] == 'j' ||
			str[i] == 'z')
			i++;
		return (i + 1);
	}
	else
		return (-1);
}

void	ft_conversion(va_list *arg, t_flags *flag, t_data *data, t_format *str)
{
	str->found = str->tmp;
	str->tmp++;
	if ((ft_clen(str->tmp) == -1))
	{
		// ft_invalid(str->tmp);
		// ft_putendl("invalid");
		if ((ft_invalid(str->tmp) == -1))
		{
			// ft_putendl("nothing here");
			str->tmp--;
			return ;
		}
		str->conv = (char *)malloc(sizeof(char) * ft_invalid(str->tmp) + 1);
		str->conv = ft_strncpy(str->conv, str->tmp, ft_invalid(str->tmp));
		str->conv[ft_invalid(str->tmp)] = '\0';
		str->tmp += (ft_invalid(str->tmp) - 1);
		// ft_putendl(str->conv);
	}
	else
	{
		// ft_putendl("valid");
		str->conv = (char *)malloc(sizeof(char) * ft_clen(str->tmp) + 1);
		str->conv = ft_strncpy(str->conv, str->tmp, ft_clen(str->tmp));
		str->conv[ft_clen(str->tmp)] = '\0';
		str->tmp += (ft_clen(str->tmp) - 1);
	}
	// ft_putendl(str->conv);
	ft_parse(str->conv, flag, arg);
	// if (flag->fw_ast || flag->p_ast)
	// 	ft_get_wp(flag, arg);
	ft_getdata(flag, arg, data);
	ft_print_conv(flag, data, str);
	// str->tmp += (ft_clen(str->tmp) - 1);
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
		{
			ft_putchar_pf(*str.tmp, &str.cnt);
			// ft_putstr("not conversion: ");
			// ft_putnbr(*str.tmp);
			// ft_putnbr(str.cnt);
			// ft_putchar('\n');
		}
		else
		{
			ft_conversion(&arg, &flag, &data, &str);
			ft_bzero(&flag, sizeof(t_flags));
			ft_bzero(&data, sizeof(t_data));
			// ft_putstr("conversion: ");
			// ft_putnbr(str.cnt);
			// ft_putchar('\n');
		}
		str.tmp++;
	}
	va_end(arg);
	return (str.cnt);
}
