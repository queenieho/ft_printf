/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:56:50 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 14:06:23 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_clen(char *str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (CONV[j])
		{
			if (str[i] == CONV[j])
				return (i + 1);
			j++;
		}
		if ((str[i] != '#' || str[i] != '0' || str[i] != '-' || str[i] != '+' ||
			str[i] != ' ' || (str[i] < '0' && str[i] > '9') || str[i] != 'h' ||
			str[i] != '*' || str[i] != '.' || str[i] != 'l' || str[i] != 'j' ||
			str[i] != 'z') && j >= 15)
		{
			return (-1);
		}
		i++;
	}
	return (-1);
}

/*
** Parses conversion string after the flags
** If field width is *, stores * flag. If Field width is a number, stores width.
*/

int	ft_getwidth(char **str, t_flags *flag, va_list *arg)
{
	char *tmp;

	tmp = *str;
	while (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
	{
		if (*tmp == '*')
		{
			flag->f_width = va_arg(*arg, int);
			if (flag->f_width < 0)
			{
				flag->f_width = - flag->f_width;
				flag->minus = 1;
			}
			// flag->fw_ast = 1;
		}
		else if (*tmp >= '0' && *tmp <= '9')
		{
			flag->f_width = ft_atoi(tmp);
			while (*tmp >= '0' && *tmp <= '9')
				tmp++;
			tmp--;
		}
		tmp++;
		*str = tmp;
	}
	// ft_putflags(*flag);
	return (1);
}

int	ft_getpres(char **str, t_flags *flag, va_list *arg)
{
	char *tmp;

	tmp = *str;
	tmp++;
	// ft_putchar(flag->conv);
	if (*tmp == '\0' || *tmp == '0' ||
		(*tmp != '*' && (*tmp < '0' && *tmp > '9')))
		flag->x_pres = 1;
	while (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
	{
		if (*tmp == '*')
		{
			flag->precision = va_arg(*arg, int);
			if (flag->precision == 0)
				flag->x_pres = 1;
			else if (flag->precision < 0)
				flag->precision = 0;
			// flag->p_ast = 1;
		}
		else if (*tmp >= '0' && *tmp <= '9')
		{
			flag->precision = ft_atoi(tmp);
			while (*tmp >= '0' && *tmp <= '9')
				tmp++;
			tmp--;
		}
		tmp++;
		*str = tmp;
	}
	// ft_putflags(*flag);
	return (1);
}

void		ft_parsenums(char **str, t_flags *flag, va_list *arg)
{
	char	*tmp;

	tmp = *str;
	// ft_putendl(*str);
	if (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
	{
		// ft_putchar(*tmp);
		// ft_putendl(" <-- getting width");
		ft_getwidth(&tmp, flag, arg);
	}
	// ft_putchar(*tmp);
	// 	ft_putendl(" <-- getting pres");
	if (*tmp == '.')
		ft_getpres(&tmp, flag, arg);
	*str = tmp;
}
