/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:58:58 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 15:41:23 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_addzero(char *str)
{
	char	*ret;
	int		j;
	int		i;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	j = ft_countspace(str);
	i = 0;
	while (str[j])
		ret[i++] = str[j++];
	while (i < ft_strlen(str))
		ret[i++] = '0';
	ret[i] = '\0';
	return (ret);
}

/*
** Making string from void *
*/

char	*ft_addhex02(char *str, int left, int sp)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1 + sp));
	if (!left)
	{
		while (str[i + 2] == ' ')
			ret[i++] = ' ';
		j = i + 2;
	}
	ret[i++] = '0';
	ret[i++] = 'X';
	while (i < ft_strlen(str))
		ret[i++] = str[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_addhex(char *str, int left)
{
	char	*ret;
	int		i;
	int		j;
	int		sp;

	i = 0;
	j = 0;
	sp = ft_countspace(str);
	if (sp < 2)
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3 - sp));
		ret[i++] = '0';
		ret[i++] = 'X';
		while (j + sp < ft_strlen(str))
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	else
		ret = ft_addhex02(str, left, sp);
	ft_strdel(&str);
	return (ret);
}

char	*ft_make_ptr(t_flags *flag, void *nb)
{
	char			*ret;
	unsigned long	num;

	num = (unsigned long)nb;
	ret = ft_itoa_base(num, 16);
	if (flag->precision || flag->x_pres)
		ret = ft_makepres(ret, flag->precision, flag->x_pres);
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);
	ret = ft_addhex(ret, flag->minus);
	if (flag->zero)
		ret = ft_addzero(ret);
	ret = ft_changecase(ret);
	return (ret);
}
