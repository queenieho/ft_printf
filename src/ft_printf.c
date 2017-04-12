/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 22:12:52 by qho               #+#    #+#             */
/*   Updated: 2017/04/11 22:44:21 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char * restrict format, ...)
{
	int			i;
	char		*found;
	char		*conv;
	char 		*tmp;
	va_list		arg;
	t_flags		flag;
	t_data		data;

	tmp = (char *)format;
	va_start(arg, format);
	i = 0;
	while (*tmp)
	{
		if (*tmp != '%')
			ft_putchar(*tmp);
		else if (*tmp == '%')
		{
			found = tmp;
			tmp++;
			if (*tmp == '%')
				ft_putchar(*tmp);
			else
			{
				conv = (char *)malloc(sizeof(char) * ft_clen(tmp) + 1);
				conv = ft_strncpy(conv, tmp, ft_clen(tmp));
				conv[ft_clen(tmp)] = '\0';
				ft_bzero(&flag, sizeof(t_flags));
				ft_bzero(&data, sizeof(t_data));

				if (ft_parse(conv, &flag) == -1)
					return (-1);
				if (flag.fw_ast)
				{
					flag.f_width = va_arg(arg, int);
					flag.fw_ast = 0;
				}
				if (flag.p_ast)
				{
					flag.precision = va_arg(arg, int);
					flag.p_ast = 0;
				}
				ft_getdata(&flag, &arg, &data);

				if (flag.conv_i >= 0 && flag.conv_i <= 5)
					ft_putstr(ft_make_num(&flag, data.nb));
				else if (flag.conv_i == 9 && flag.lm == 0)
					ft_putstr(ft_make_c(&flag, data.c));
				else if ((flag.conv_i == 10 && flag.lm == 0) || (flag.conv_i == 9 && flag.lm == 3))
					ft_putwstr(ft_make_wc(&flag, data.w_chr));
				else if (flag.conv_i == 11 && flag.lm == 0)
					ft_putstr(ft_make_s(&flag, data.str));
				else if ((flag.conv_i == 12 && flag.lm == 0) || (flag.conv_i == 11 && flag.lm == 3))
					ft_putwstr(ft_make_wstr(&flag, data.w_str));
				else if (flag.conv_i == 13)
					ft_putstr(ft_make_ptr(data.ptr));
				else
					ft_putendl("else?");
				tmp += (ft_clen(tmp) - 1);
				free(conv);
				conv = NULL;
			}
		}
		tmp++;
	}
	va_end(arg);
	return (i);
}