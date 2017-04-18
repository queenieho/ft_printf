/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_pres.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:37:16 by qho               #+#    #+#             */
/*   Updated: 2017/04/18 13:16:30 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** WIDTH
*/

char 	*ft_makewide02(char *str, int width, int left)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (width + 1));
	if (left)
	{
		while (str[j])
			ret[i++] = str[j++];
		while (i < width)
			ret[i++] = ' ';
		ret[i] = '\0';
	}
	else
	{
		width = width - ft_strlen(str);
		while (i < width)
			ret[i++] = ' ';
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	return (ret);
}

char	*ft_makewide(char *str, int width, int left)
{
	// ft_putendl("making width");
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (width > ft_strlen(str))
		ret = ft_makewide02(str, width, left);
	else
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	// ft_putendl(ret);
	ft_strdel(&str);
	return (ret);
}

/*
** PRECISION
*/

char	*ft_makepres02(char *str, int j, int pres)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * (pres + 1));
	i = pres;
	ret[i] = '\0';
	while ((i + 1) && (j + 1))
	{
		if (str[j] != ' ')
			ret[--i] = str[j--];
		else if (pres > 0)
			ret[--i] = '0';
		pres--;
	}
	while (i + 1)
	{
		if (pres > 0)
			ret[--i] = '0';
		else
			ret[--i] = ' ';
		pres--;
	}
	return (ret);
}

char	*ft_makepres(char *str, int pres, int x_flag)
{
	char	*ret;
	int		i;
	int		j;

	i = ft_strlen(str);
	j = i - 1;
	// ft_putnbr(x_flag);
	// ft_putnbr(x_flag);
	// ft_putchar('\n');
	if (pres > i)
		ret = ft_makepres02(str, j, pres);
	else if (pres == 0 && x_flag == 1)
	{
		ret = (char *)malloc(sizeof(char) * 1);
		ret[0] = '\0';
	}
	else
	{
		ret = (char *)malloc(sizeof(char) * (i + 1));
		ret[i] = '\0';
		while ((i + 1) && (j + 1))
			ret[--i] = str[j--];
	}
	ft_strdel(&str);
	return (ret);
}
