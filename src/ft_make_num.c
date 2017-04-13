/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:13:18 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 09:47:35 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checking flags
*/

void		ft_checkflags(t_flags *flag, unsigned long long nb)
{
	if (flag->precision)
		flag->zero = 0;
	if (flag->hash)
		if ((flag->conv != 'o' && flag->conv != 'O' &&
			flag->conv != 'x' && flag->conv != 'X') || nb == 0)
			flag->hash = 0;
	if (flag->zero)
	{
		if (flag->conv_i > 8)
			flag->zero = 0;
		if (flag->minus)
			flag->zero = 0;
	}
	if (flag->plus)
	{
		if (flag->conv != 'd' && flag->conv != 'D' && flag->conv != 'i')
			flag->plus = 0;
		flag->space = 0;
	}
	if (flag->space)
		if ((flag->conv != 'd' && flag->conv != 'D' && flag->conv != 'i')
			|| flag->plus)
			flag->space = 0;
}

/*
** ********************************* **
** Making strings from the arguments **
** ********************************* **
*/

/*
** ITOA BASE
*/

static int	val_size(unsigned long long value, int base)
{
	int size;

	size = 0;
	while ((value * base) / base)
	{
		size++;
		value /= base;
	}
	return (size);
}

char		*ft_itoa_base(unsigned long long value, int base)
{
	char	*s;
	int		i;
	int		size;

	i = 0;
	if (value == 0)
	{
		s = (char *)malloc(sizeof(char) * 2);
		s[0] = '0';
		s[1] = '\0';
	}
	else
	{
		size = val_size(value, base);
		s = (char *)malloc(sizeof(char) * (size + 1));
		i = size - 1;
		while (value)
		{
			s[i] = BASE[value % base];
			i--;
			value /= base;
		}
		s[size] = '\0';
	}
	return (s);
}

/*
** Making string from int
*/

char		*ft_make_num(t_flags *flag, unsigned long long nb)
{
	// ft_putendl("make num?");
	char	*ret;
	int		base;

	if (flag->conv == 'o' || flag->conv == 'O')
		base = 8;
	else if (flag->conv == 'x' || flag->conv == 'X')
		base = 16;
	else
		base = 10;
	ret = ft_itoa_base(nb, base);
	ft_checkflags(flag, nb);
	// ft_putendl("flags checked");
	if (flag->precision)
		ret = ft_makepres(ret, flag->precision);
	// ft_putendl("make pres?");
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);
	// ft_putendl("make width?");
	// ft_putendl(ret);
	if (flag->plus || flag->space || flag->hash || flag->neg || flag->zero)
		ret = ft_modnum(ret, flag, flag->neg);
	// ft_putendl("make mod?");
	if (flag->conv == 'x')
		ret = ft_changecase(ret);
	// ft_putendl("make num end?");
	return (ret);
}
