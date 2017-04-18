/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:15:55 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 15:48:52 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Modifying according to flags BLERGH
** if (flag->plus || flag->space || flag->hash || neg || flag->zero)
*/

char	*ft_modnum022(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 1;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++j] == ' ')
		ret[i++] = ' ';
	ret[i++] = '0';
	ret[i++] = 'x';
	while (str[j])
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_modnum021(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str[0] != ' ' && str[0] != '0')
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		ret[i++] = '0';
		ret[i++] = 'x';
		while (i < ft_strlen(str))
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	else
		ret = ft_modnum022(str);
	return (ret);
}

char	*ft_modnum02(char *str, int sp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (sp >= 2)
		ret = ft_modnum021(str);
	else
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3 - sp));
		ret[i++] = '0';
		ret[i++] = 'X';
		while (j < ft_strlen(str))
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	return (ret);
}

char	*ft_modnum03(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[j])
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_modnum(char *str, t_flags *flag, int neg)
{
	int		sp;
	char	*ret;
	int		i;
	int		j;

	sp = ft_countspace(str);
	i = 0;
	j = 0;
	if (flag->zero)
	{
		while (str[i] == ' ')
			str[i++] = '0';
		j++;
	}
	if (flag->plus || flag->space || neg ||
		(flag->hash && (flag->conv == 'o' || flag->conv == 'O')))
		ret = ft_modnum01(str, flag, neg, sp);
	else if (flag->hash && (flag->conv == 'x' || flag->conv == 'X'))
		ret = ft_modnum02(str, sp);
	else
		ret = ft_modnum03(str);
	ft_strdel(&str);
	return (ret);
}
