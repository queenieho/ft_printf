/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:56:39 by qho               #+#    #+#             */
/*   Updated: 2017/04/19 23:35:48 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char(t_flags *flag, t_data *data, t_format *str)
{
	char	*print;
	wchar_t	*w_print;

	print = NULL;
	w_print = NULL;
	if (flag->conv_i == 9 && flag->lm == 0)
	{
		if (data->c == '\0' && flag->minus)
			ft_putchar_pf('\0', &str->cnt);
		print = ft_make_c(flag, data->c, &str->cnt);
		ft_putstr_pf(print, &str->cnt);
		if (data->c == '\0' && !flag->minus)
			ft_putchar_pf('\0', &str->cnt);
	}
	else if ((flag->conv_i == 10) ||
		(flag->conv_i == 9 && flag->lm == 3))
	{
		if (data->w_chr == '\0' && flag->minus)
			ft_putwchar_pf('\0', &str->cnt);
		w_print = ft_make_wc(flag, data->w_chr, str);
		ft_putwstr_pf(w_print, &str->cnt);
		if (data->w_chr == '\0' && !flag->minus)
			ft_putwchar_pf('\0', &str->cnt);
	}
	if (print)
		free(print);
	if (w_print)
		free(w_print);
}

void	ft_print_conv(t_flags *flag, t_data *data, t_format *str)
{
	char	*print;

	print = NULL;
	if (flag->conv_i >= 0 && flag->conv_i <= 8)
		print = ft_make_num(flag, data->nb);
	else if (flag->conv_i == 9 || flag->conv_i == 10)
		ft_print_char(flag, data, str);
	else if (flag->conv_i == 11 && flag->lm == 0)
		print = ft_make_s(flag, data->str);
	else if ((flag->conv_i == 12) || (flag->conv_i == 11 && flag->lm == 3))
		ft_putwstr_pf(ft_make_wstr(flag, data->w_str), &str->cnt);
	else if (flag->conv_i == 13)
		print = ft_make_ptr(flag, data->ptr);
	else if (flag->conv_i == 14)
		print = ft_make_c(flag, data->c, &str->cnt);
	else if (flag->conv_i == -1 && flag->conv != '\0')
		print = ft_make_c(flag, flag->conv, &str->cnt);

	ft_putstr_pf(print, &str->cnt);
	if (print)
		free(print);
}

int		ft_invalid(char *str)
{
	int i;

	i = 0;
	if (str[i])
	{
		while (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == '+'
			|| str[i] == ' ' || (str[i] >= '0' && str[i] <= '9')
			|| str[i] == 'h' || str[i] == '*' || str[i] == '.' || str[i] == 'l'
			|| str[i] == 'j' || str[i] == 'z')
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
		if ((ft_invalid(str->tmp) == -1))
		{
			str->tmp--;
			return ;
		}
		str->conv = (char *)malloc(sizeof(char) * (ft_invalid(str->tmp) + 1));
		str->conv = ft_strncpy(str->conv, str->tmp, (ft_invalid(str->tmp)));
		str->conv[ft_invalid(str->tmp)] = '\0';
		str->tmp += (ft_invalid(str->tmp) - 1);
	}
	else
	{
		str->conv = (char *)malloc(sizeof(char) * (ft_clen(str->tmp) + 1));
		str->conv = ft_strncpy(str->conv, str->tmp, (ft_clen(str->tmp)));
		str->conv[ft_clen(str->tmp)] = '\0';
		str->tmp += (ft_clen(str->tmp) - 1);
	}
	ft_parse(str->conv, flag, arg);
	ft_getdata(flag, arg, data);
	ft_print_conv(flag, data, str);
	ft_strdel(&str->conv);
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

// int		ft_printf(const char *restrict format, ...)
// {
// 	va_list		arg;
// 	t_flags		*flag;
// 	t_data		*data;
// 	t_format	*str;

// 	va_start(arg, format);
// 	flag = (t_flags*)malloc(sizeof(t_flags));
// 	data = (t_data*)malloc(sizeof(t_data));
// 	str = (t_format*)malloc(sizeof(t_format));
// 	ft_bzero(str, sizeof(t_format));
// 	ft_bzero(flag, sizeof(t_flags));
// 	ft_bzero(data, sizeof(t_data));
// 	str->tmp = (char *)format;
// 	while (*str->tmp)
// 	{
// 		if (*str->tmp != '%')
// 			ft_putchar_pf(*str->tmp, &str->cnt);
// 		else
// 		{
// 			ft_conversion(&arg, flag, data, str);
// 			ft_bzero(flag, sizeof(t_flags));
// 			ft_bzero(data, sizeof(t_data));
// 		}
// 		str->tmp++;
// 	}
// 	va_end(arg);
// 	return (str->cnt);
// }
