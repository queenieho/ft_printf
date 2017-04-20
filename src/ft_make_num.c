/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:13:18 by qho               #+#    #+#             */
/*   Updated: 2017/04/19 23:05:51 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checking flags
*/

void		ft_checkflags(t_flags *f, unsigned long long nb)
{
	if (f->x_pres && (nb || (f->hash && (f->conv == 'o' || f->conv == 'O'))))
		f->x_pres = 0;
	if (f->precision)
		f->zero = 0;
	if (f->hash)
		if ((f->conv != 'o' && f->conv != 'O' && f->conv != 'x' &&
			f->conv != 'X') || (nb == 0 && (f->conv == 'o' || f->conv == 'O' ||
			f->conv == 'x' || f->conv == 'X')))
			f->hash = 0;
	if (f->zero)
	{
		if (f->minus)
			f->zero = 0;
	}
	if (f->plus)
	{
		if (f->conv != 'd' && f->conv != 'D' && f->conv != 'i')
			f->plus = 0;
		f->space = 0;
	}
	if (f->space)
		if ((f->conv != 'd' && f->conv != 'D' && f->conv != 'i') || f->plus)
			f->space = 0;
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
	if ((long)value == LONG_MIN && base == 10)
		s = ft_strdup("9223372036854775808");
	else if ((long)value == LONG_MIN && base == 8)
		s = ft_strdup("1000000000000000000000");
	else if (value == 0)
		s = ft_strdup("0");
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
	if (flag->precision || flag->x_pres)
		ret = ft_makepres(ret, flag->precision, flag->x_pres);
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);
	if (flag->plus || flag->space || flag->hash || flag->neg || flag->zero)
		ret = ft_modnum(ret, flag, flag->neg);
	if (flag->conv == 'x')
		ret = ft_changecase(ret);
	return (ret);
}
