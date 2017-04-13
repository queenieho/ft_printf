/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 23:52:06 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 09:08:52 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Parsing [flags].
**	Checks first 5 chars, and stores flags found.
**	Returns number of flags found if it finds [Field width] or finishes the 5.
**	If invalid, return (-1)
*/

int		ft_parseflags(char *str, t_flags *flag)
{
	int i;

	i = 0;
	while (i < 5 && str[i])
	{
		if (str[i] == '#')
			flag->hash = 1;
		else if (str[i] == '0')
			flag->zero = 1;
		else if (str[i] == '-')
			flag->minus = 1;
		else if (str[i] == '+')
			flag->plus = 1;
		else if (str[i] == ' ')
			flag->space = 1;
		else if (str[i] == '*' || (str[i] > '0' && str[i] < '9')
			|| str[i] == '.' || str[i] == 'h' || str[i] == 'l' ||
			str[i] == 'j' || str[i] == 'z')
			return (flag->hash + flag->zero + flag->minus +
				flag->plus + flag->space);
		else
			return (-1);
		i++;
	}
	return (flag->hash + flag->zero + flag->minus + flag->plus + flag->space);
}

void	ft_parselenmod(char **str, t_flags *flag)
{
	char *tmp;

	tmp = *str;
	if (!(ft_strcmp(tmp, "hh")))
		flag->lm = 1;
	else if (!(ft_strcmp(tmp, "h")))
		flag->lm = 2;
	else if (!(ft_strcmp(tmp, "l")))
		flag->lm = 3;
	else if (!(ft_strcmp(tmp, "ll")))
		flag->lm = 4;
	else if (!(ft_strcmp(tmp, "j")))
		flag->lm = 5;
	else if (!(ft_strcmp(tmp, "z")))
		flag->lm = 6;
	else if (*tmp == '\0')
		flag->lm = 0;
	if (flag->lm == 1 || flag->lm == 4)
		tmp += 2;
	else if (flag->lm == 2 || flag->lm == 3 || flag->lm == 5 || flag->lm == 6)
		tmp++;
	*str = tmp;
}

int	ft_parseconv(char c)
{
	int i;

	i = 0;
	while (CONV[i])
	{	
		if (CONV[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
** Parses conversion string
** Stores the conversion.
*/

int	ft_parse(char *str, t_flags *flag)
{
	int i;
	int	flags;
	int	len;

	// ft_putendl("parsing?");
	i = 0;
	len = ft_strlen(str);
	flag->conv_i = ft_parseconv(str[(len - 1)]);
	flag->conv = str[(len - 1)];
	str[(len - 1)] = '\0';
	flags = ft_parseflags(str, flag);
	str += flags;
	ft_parsenums(&str, flag);
	ft_parselenmod(&str, flag);
	return (1);
}
