// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_printf.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2017/02/21 21:46:14 by qho               #+#    #+#             */
// /*   Updated: 2017/04/04 14:25:52 by qho              ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "ft_printf.h"

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	ft_putstr(char const *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s)
// 	{
// 		while (s[i])
// 		{
// 			ft_putchar(s[i]);
// 			i++;
// 		}
// 	}
// }

 
// void	ft_putnbr(long nb)
// {
// 	unsigned long long num;

// 	if (nb < 0)
// 	{
// 		ft_putchar('-');
// 		num = (unsigned long long)-nb;
// 	}
// 	if (nb >= 0)
// 		num = (unsigned long long)nb;
// 	if (num >= 10)
// 	{
// 		ft_putnbr(num / 10);
// 		ft_putnbr(num % 10);
// 	}
// 	else
// 	{
// 		ft_putchar('0' + num);
// 	}
// }

// int	ft_strlen(const char *s)
// {
// 	unsigned int i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	return (i);
// }

// void	ft_strdel(char **as)
// {
// 	if (as)
// 	{
// 		free(*as);
// 		*as = NULL;
// 	}
// }

// void	ft_memdel(void **ap)
// {
// 	unsigned char	**str;

// 	if (ap)
// 	{
// 		str = (unsigned char **) ap;
// 		free((void *) *str);
// 		*ap = NULL;
// 	}
// }

// /* 
// * STRCPY
// */

// char	*ft_strcpy(char *dst, const char *src)
// {
// 	unsigned int i;

// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

// char	*ft_strdup(const char *s1)
// {
// 	unsigned int	i;
// 	char			*dst;

// 	i = 0;
// 	dst = (char *)malloc(ft_strlen(s1) + 1);
// 	if (dst != NULL)
// 	{
// 		ft_strcpy(dst, s1);
// 		return (dst);
// 	}
// 	else
// 		return (0);
// }

// /*
// ** char to wchar
// */

// wchar_t	*ft_ctowc(char *str)
// {
// 	wchar_t *wstr;
// 	int i;

// 	i = 0;
// 	if (!(wstr = (wchar_t *)malloc(sizeof(wchar_t) * (ft_strlen(str) + 1))))
// 		return (NULL);
// 	while (str[i])
// 	{
// 		wstr[i] = (wchar_t)str[i];
// 		i++;
// 	}
// 	wstr[i] = '\0';
// 	return (wstr);
// }

// int ft_printf(const char * restrict format, ...)
// {
// 	int i;
// 	va_list arg;
// 	long nb;
// 	char *tmp;
// 	char *str;
// 	wchar_t *wstr;

// 	i = 0;
// 	va_start(arg, format);
// 	tmp = ft_strdup(format);
// 	while (tmp[i])
// 	{
// 		if (tmp[i] != '%')
// 			ft_putchar(tmp[i]);
// 		if (tmp[i] == '%')
// 		{
// 			i++;
// 			if (tmp[i] == '%')
// 				ft_putchar('%');
// 			else if (tmp[i] == 's')
// 			{
// 				str = ft_strdup(va_arg(arg, char *));
// 				ft_putstr(str);
// 			}
// 			else if (tmp[i] == 'S')
// 			{
// 				str = ft_strdup(va_arg(arg, char *));
// 				wstr = ft_ctowc(str);
// 				ft_putstr((char *)wstr);
// 			}
// 			else if (tmp[i] == 'd' || tmp[i] == 'i')
// 			{
// 				nb = va_arg(arg, int);
// 				ft_putnbr(nb);
// 			}
// 			else if (tmp[i] == 'D')
// 			{
// 				nb = va_arg(arg, int);
// 				if (nb < 0)
// 					nb = UINT_MAX + nb + 1;
// 				ft_putnbr(nb);
// 			}
// 			else if (tmp[i] == 'u' || tmp[i] == 'U')
// 			{
// 				nb = va_arg(arg, int);
// 				if (nb < 0)
// 					nb = UINT_MAX + nb + 1;
// 				ft_putnbr(nb);
// 			}
// 			else if (tmp[i] == 'o' || tmp[i] == 'O')
// 			{
// 				nb = va_arg(arg, int);
// 				if (nb < 0)
// 					nb = UINT_MAX + nb + 1;
// 				ft_putstr(ft_itoa_base(nb, 8));
// 			}
// 			else if (tmp[i] == 'X')
// 			{
// 				nb = va_arg(arg, int);
// 				if (nb < 0)
// 					nb = UINT_MAX + nb + 1;
// 				ft_putstr(ft_itoa_base(nb, 16));
// 			}
// 			else if (tmp[i] == 'x')
// 			{
// 				nb = va_arg(arg, int);
// 				if (nb < 0)
// 					nb = UINT_MAX + nb + 1;
// 				ft_putstr(ft_changecase(ft_itoa_base(nb, 16)));
// 			}
// 			else if (tmp[i] == 'c')
// 			{
// 				ft_putchar(va_arg(arg, int));
// 			}
// 			else if (tmp[i] == 'C')
// 			{
// 				ft_putchar(va_arg(arg, int));
// 			}

// 		}
// 		i++;
// 	}
// 	va_end(arg);
// 	return (0);
// }
