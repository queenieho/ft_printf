/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 13:04:55 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 10:02:45 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Making string from char
*/

char	*ft_make_c(t_flags *flag, int c, int *cnt)
{
	char	*ret;
	int		n_cnt;

	n_cnt = 0;
	ft_checkflags(flag, 0);
	if (c)
	{
		ret = (char *)malloc(sizeof(char) * 2);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		ret = (char *)malloc(sizeof(char) * 1);
		ret[0] = '\0';
		n_cnt = 1;
	}
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width - n_cnt, flag->minus);
	*cnt += n_cnt;
	return (ret);
}

/*
** Making string from string!
*/

char	*ft_makepres_s(char *str, int pres)
{
	char	*ret;
	int		i;

	i = -1;
	if (pres < ft_strlen(str))
	{
		ret = (char *)malloc(sizeof(char) * (pres + 1));
		while (++i < pres)
			ret[i] = str[i];
		ret[i] = '\0';
	}
	else
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		while (str[++i])
			ret[i] = str[i];
		ret[i] = '\0';
	}
	ft_strdel(&str);
	return (ret);
}

char	*ft_make_s(t_flags *flag, char *str)
{
	char *ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ret = ft_strncpy(ret, str, (ft_strlen(str) + 1));
	ft_checkflags(flag, 0);
	if (flag->precision)
		ret = ft_makepres_s(ret, flag->precision);
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);
	return (ret);
}
