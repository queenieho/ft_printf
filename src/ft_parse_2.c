/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:56:50 by qho               #+#    #+#             */
/*   Updated: 2017/04/12 16:26:06 by qho              ###   ########.fr       */
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
		i++;
	}
	return (i);
}

/*
** Parses conversion string after the flags
** If field width is *, stores * flag. If Field width is a number, stores width.
*/

int	ft_getwidth(char **str, t_flags *flag)
{
	char *tmp;

	tmp = *str;
	while (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
	{
		if (*tmp == '*')
		{
			if (flag->fw_ast || flag->f_width)
				return (-1);
			flag->fw_ast = 1;
		}
		else if (*tmp >= '0' && *tmp <= '9')
		{
			if (flag->fw_ast || flag->f_width)
				return (-1);
			flag->f_width = ft_atoi(tmp);
			while (*tmp >= '0' && *tmp <= '9')
				tmp++;
			tmp--;
		}
		tmp++;
		*str = tmp;
	}
	return (1);
}

int	ft_getpres(char **str, t_flags *flag)
{
	char *tmp;

	tmp = *str;
	tmp++;
	while (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
	{
		if (*tmp == '*')
		{
			if (flag->p_ast || flag->precision)
				return (-1);
			flag->p_ast = 1;
		}
		else if (*tmp >= '0' && *tmp <= '9')
		{
			if (flag->p_ast || flag->precision)
				return (-1);
			flag->precision = ft_atoi(tmp);
			while (*tmp >= '0' && *tmp <= '9')
				tmp++;
			tmp--;
		}
		tmp++;
		*str = tmp;
	}
	return (1);
}

void		ft_parsenums(char **str, t_flags *flag)
{
	char	*tmp;

	tmp = *str;
	if (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
		ft_getwidth(&tmp, flag);
	if (*tmp == '.')
		ft_getpres(&tmp, flag);
	*str = tmp;
}
