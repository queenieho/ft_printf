/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modnum_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:10:40 by qho               #+#    #+#             */
/*   Updated: 2017/04/12 14:11:19 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_countspace(char *str)
{
	int		sp;

	sp = 0;
	while (*str)
	{
		if (*str == ' ')
			sp++;
		str++;
	}
	return (sp);
}

char	ft_addsign(t_flags *flag, int neg)
{
	if (neg)
		return ('-');
	else if (flag->plus && !neg)
		return ('+');
	else if (flag->space && !neg)
		return (' ');
	else if (flag->hash)
		return ('0');
	return (0);
}

char	*ft_modnum011(char *str, t_flags *flag, int neg)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (str[0] != ' ')
	{
		ret[i++] = ft_addsign(flag, neg);
		while (i < ft_strlen(str))
			ret[++i] = str[j++];
		ret[i] = '\0';
	}
	else
	{
		while (str[++j] == ' ')
			ret[i++] = ' ';
		ret[i++] = ft_addsign(flag, neg);
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	return (ret);
}

char	*ft_modnum01(char *str, t_flags *flag, int neg, int sp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (sp)
		ret = ft_modnum011(str, flag, neg);
	else
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
		ret[i++] = ft_addsign(flag, neg);
		while (j < ft_strlen(str))
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	return (ret);
}
