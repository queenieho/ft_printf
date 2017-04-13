/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:58:58 by qho               #+#    #+#             */
/*   Updated: 2017/04/12 15:01:24 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Making string from void *
*/

char	*ft_addhex(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3));
	ret[i++] = '0';
	ret[i++] = 'X';
	while (j < ft_strlen(str))
		ret[i++] = str[j++];
	ret[i] = '\0';
	ft_strdel(&str);
	return (ret);
}

char	*ft_make_ptr(void *nb)
{
	char			*ret;
	unsigned long	num;

	num = (unsigned long)nb;
	ret = ft_itoa_base(num, 16);
	ret = ft_addhex(ret);
	ret = ft_changecase(ret);
	return (ret);
}
