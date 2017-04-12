/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 23:52:06 by qho               #+#    #+#             */
/*   Updated: 2017/04/11 22:32:24 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** All the writing functions here
*/

void	ft_putchar(char c)
{
	write(1, &c, 1);
	// ADD COUNTER FOR EACH CHAR PRINTED
}

void	ft_putstr(char const *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar(s[i]);
			i++;
		}
	}
}

 
void	ft_putnbr(long long nb)
{
	unsigned long long num;

	if (nb < 0)
	{
		ft_putchar('-');
		num = (unsigned long long)-nb;
	}
	if (nb >= 0)
		num = (unsigned long long)nb;
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		ft_putchar('0' + num);
	}
}

/*
** FUNCTION TO WRITING WCHARS
*/

void	ft_putwchar(wchar_t c)
{
	// ft_putendl("putting wchar?");
	if (c <= 0x7F)
		ft_putchar(c);
	else if (c <= 0x7FF)
	{
		ft_putchar(0xC0 | (c >> 6));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar(0xC0 | (c >> 12));
		ft_putchar(0x80 | ((c >> 6) & 0x3F));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c <= 0x1FFFF)
	{
		ft_putchar(0xC0 | (c >> 18));
		ft_putchar(0x80 | ((c >> 12) & 0x3F));
		ft_putchar(0x80 | ((c >> 6) & 0x3F));
		ft_putchar(0x80 | (c & 0x3F));
	}
}

void	ft_putwstr(wchar_t *str)
{
	// ft_putendl("string wchar?");
	while (*str)
	{
		// ft_putendl("putting str");
		ft_putwchar(*str++);
		// str++;
	}
}


/*
** FUNCTION TO PRINT OUT FLAG STRUCT
*/

void	ft_putflags(t_flags flag)
{
	ft_putstr("flags hash: ");
	ft_putnbr(flag.hash);
	ft_putchar('\n');
	ft_putstr("flags zero: ");
	ft_putnbr(flag.zero);
	ft_putchar('\n');
	ft_putstr("flags minus: ");
	ft_putnbr(flag.minus);
	ft_putchar('\n');
	ft_putstr("flags plus: ");
	ft_putnbr(flag.plus);
	ft_putchar('\n');
	ft_putstr("flags space: ");
	ft_putnbr(flag.space);
	ft_putchar('\n');
	ft_putstr("fw *: ");
	ft_putnbr(flag.fw_ast);
	ft_putchar('\n');
	ft_putstr("fw: ");
	ft_putnbr(flag.f_width);
	ft_putchar('\n');
	ft_putstr("pres *: ");
	ft_putnbr(flag.p_ast);
	ft_putchar('\n');
	ft_putstr("pres: ");
	ft_putnbr(flag.precision);
	ft_putchar('\n');
	ft_putstr("length mod: ");
	ft_putnbr(flag.lm);
	ft_putchar('\n');
	ft_putstr("conversion: ");
	ft_putchar(flag.conv);
	ft_putchar('\n');
	ft_putstr("conversion i: ");
	ft_putnbr(flag.conv_i);
	ft_putchar('\n');

}

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	ft_putchar('\n');
}

void	ft_error(char *str)
{
	ft_putendl(str);
}

char	*ft_strcpy(char *dst, const char *src)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*dst;

	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + 1);
	if (dst != NULL)
	{
		ft_strcpy(dst, s1);
		return (dst);
	}
	else
		return (0);
}

void	ft_strdel(char **str)
{
	free(*str);
	*str = NULL;
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*s1a;
	unsigned char	*s2a;

	i = 0;
	s1a = (unsigned char *)s1;
	s2a = (unsigned char *)s2;
	if (s1a[i] == '\0')
		return (s1a[i] - s2a[i]);
	while (s1a[i] != '\0' || s2a[i] != '\0')
	{
		if (s2a[i] == '\0')
			return (s1a[i]);
		else if (s2a[i] != s1a[i])
			return (s1a[i] - s2a[i]);
		i++;
	}
	return (0);
}

char	*ft_strncpy(char *dst, char const *src, size_t len)
{
	char *dst2;

	dst2 = dst;
	while (len && *src)
	{
		*dst2++ = *src++;
		len--;
	}
	while (len)
	{
		*dst2++ = '\0';
		len--;
	}
	return (dst);
}

int	ft_strlen(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s2;
	size_t			i;

	s2 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s2[i] = 0;
		i++;
	}
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				sign;
	int				ans;

	i = 0;
	ans = 0;
	sign = 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ans = ans * 10;
		ans = ans + (str[i] - '0');
		i++;
	}
	return (ans);
}

/*
**	Parsing [flags].
**	Checks first 5 chars, and stores flags found.
**	Returns number of flags found if it finds [Field width] or finishes the 5.
**	If invalid, return (-1)
*/

int	ft_parseflags(char *str, t_flags *flag)
{
	int i;

	i = 0;
	while(i < 5 && str[i])
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
		else if (str[i] == '*' || (str[i] > '0' && str[i] < '9') || str[i] == '.'
			|| str[i] == 'h' || str[i] == 'l' || str[i] == 'j' || str[i] == 'z')
			return (flag->hash + flag->zero + flag->minus + flag->plus + flag->space);
		else
			return (-1);
		i++;
	}
	return (flag->hash + flag->zero + flag->minus + flag->plus + flag->space);
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

int	ft_parsenums(char **str, t_flags *flag)
{
	char	*tmp;

	tmp = *str;
	if (*tmp == '*' || (*tmp >= '0' && *tmp <= '9'))
		if ((ft_getwidth(&tmp, flag)) == -1)
			ft_putstr("* and digits?\n");
	if (*tmp == '.')
	{
		if ((ft_getpres(&tmp, flag)) == -1)
			ft_putstr("* and digits?\n");
	}
	*str = tmp;
	return (1);
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

int	ft_parselenmod(char **str, t_flags *flag)
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
	return(-1);
}


/*
** Parses conversion string
** Stores the conversion.
*/

int	ft_parse(char *str, t_flags *flag)
{
	// ft_putendl("parsing conversions");
	// ft_putendl(str);

	int i;
	int	flags;
	int	len;

	i = 0;
	len = ft_strlen(str);
	if ((flag->conv_i = ft_parseconv(str[(len - 1)]) == -1))
	{
		ft_error("Invalid conversion");
		return (-1);
	}
	flag->conv_i = ft_parseconv(str[(len - 1)]);
	flag->conv = str[(len - 1)];
	str[(len - 1)] = '\0';
	// ft_putendl(str);
	// if (!(flags = ft_parseflags(str, flag)))
	// 	return (-1);
	flags = ft_parseflags(str, flag);
	str += flags;
	// ft_putendl(str);
	ft_parsenums(&str, flag);
	ft_parselenmod(&str, flag);

	return (1);
}

int	ft_clen(char *str)
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
** WIDTH
*/

char	*ft_makewide(char *str, int width, int left)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (width > ft_strlen(str))
	{
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
			while (i < (width - ft_strlen(str)))
				ret[i++] = ' ';
			while (str[j])
				ret[i++] = str[j++];
			ret[i] = '\0';
		}
	}
	else
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	ft_strdel(&str);
	return (ret);
}

/*
** PRECISION
*/

char	*ft_makepres(char *str, int pres)
{
	char	*ret;
	int		i;
	int		j;

	i = ft_strlen(str);
	j = i - 1;
	if (pres > i)
	{
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

/*
** Change hex to lowercase for x conversion
*/

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}

char *ft_changecase(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

/*
** Modifying according to flags BLERGH
** if (flag->plus || flag->space || flag->hash || neg || flag->zero)
*/


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
	i = 0;
	if (flag->plus || flag->space || neg || 
		(flag->hash && (flag->conv == 'o' || flag->conv == 'O')))
	{
		if (sp)
		{
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
		}
		else
		{
			ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
			ret[i++] = ft_addsign(flag, neg);
			while (j < ft_strlen(str))
				ret[i++] = str[j++];
			ret[i] = '\0';
		}
	}
	else if (flag->hash && (flag->conv == 'x' || flag->conv == 'X'))
	{
		if (sp >= 2)
		{
			ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
			if (str[0] != ' ')
			{
				ret[i++] = '0';
				ret[i++] = 'x';
				while (i < ft_strlen(str))
					ret[i++] = str[++j];
				ret[i] = '\0';
			}
			else
			{
				j++;
				while (str[++j] == ' ')
					ret[i++] = ' ';
				ret[i++] = '0';
				ret[i++] = 'x';
				while (str[j])
					ret[i++] = str[j++];
				ret[i] = '\0';
			}
		}
		else
		{
			ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 3 - sp));
			ret[i++] = '0';
			ret[i++] = 'X';
			while (j < ft_strlen(str))
				ret[i++] = str[j++];
			ret[i] = '\0';
		}
	}
	else
	{
		j = 0;
		ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	ft_strdel(&str);
	return (ret);
}

/*
** Checking flags
*/

void	ft_checkflags(t_flags *flag)
{
	if (flag->precision)
		flag->zero = 0;
	if (flag->hash)
		if (flag->conv != 'o' && flag->conv != 'O' && flag->conv != 'x' && flag->conv != 'X')
			flag->hash = 0;
	if (flag->zero)
	{
		if (flag->conv_i > 8)
			flag->zero = 0;
		if (flag->minus)
			flag->zero = 0;
	}
	if (flag->plus)
	{
		if (flag->conv != 'd' && flag->conv != 'D' && flag->conv != 'i')
			flag->plus = 0;
		flag->space = 0;
	}
	if (flag->space)
		if ((flag->conv != 'd' && flag->conv != 'D' && flag->conv != 'i') || flag->plus)
			flag->space = 0;
}

/* ********************************* **
** Making strings from the arguments **
** ********************************* */

/*
** ITOA BASE
*/

static int		val_size(unsigned long long value, int base)
{
	int size;

	size = 0;
	while ((value * base)/ base)
	{
		size++;
		value /= base;
	}
	return  (size);
}

char	*ft_itoa_base(unsigned long long value, int base)
{
	char *s;
	int i;
	int size;
	// int neg;

	i = 0;
	// neg = 0;
	if (value == 0)
	{
		s = (char *) malloc(sizeof(char) * 2);
		s = "0";
	}
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

char	*ft_make_num(t_flags *flag, unsigned long long nb)
{
	char	*ret;
	int		base;
	
	if (flag->conv == 'o' || flag->conv == 'O')
		base = 8;
	else if (flag->conv == 'x' || flag->conv == 'X')
	{
		// ft_putendl("base 16");
		base = 16;
	}
	else
		base = 10;
	ret = ft_itoa_base(nb, base);
	// ft_putstr("itoa: ");
	// ft_putendl(ret);
	ft_checkflags(flag);
	if (flag->precision)
		ret = ft_makepres(ret, flag->precision);
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);

	// ft_putendl(ret);
	if (flag->plus || flag->space || flag->hash || flag->neg || flag->zero) //what about a negative number?
	{
		// ft_putendl("mod beginning");
		ret = ft_modnum(ret, flag, flag->neg);
		// ft_putstr("flags: ");
	}
	if (flag->conv == 'x')
		ret = ft_changecase(ret);
	return (ret);
}

/*
** Making string from char
*/

char	*ft_make_c(t_flags *flag, int c)
{
	char	*ret;
	int		n_cnt;

	n_cnt = 0;
	ft_checkflags(flag);

	// REMEMBER TO COUNT +1 WHEN IT'S A NULL CHAR
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

	// ft_putendl("strings");
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	ret = ft_strncpy(ret, str, (ft_strlen(str) + 1));
	ft_checkflags(flag);
	if (flag->precision)
		ret = ft_makepres_s(ret, flag->precision);
	if (flag->f_width)
		ret = ft_makewide(ret, flag->f_width, flag->minus);
	return (ret);
}


/* ***************************** *\
** Making w_string from w_char!
\* ***************************** */


/*
** Applying width to w_char
*/

int ft_wchar_len(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else
		return (4);
}


int	ft_wstr_len(const wchar_t *ws)
{
	unsigned int i;

	i = 0;
	while (*ws)
	{
		i += (ft_wchar_len(*ws));
		ws++;
	}
	return (i);
}

wchar_t	*ft_makewide_ws(wchar_t *str, int width, int left)
{
	wchar_t	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// ft_putendl("making wide string");
	if (width > ft_wstr_len(str))
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (width + 1));
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
			while (i < (width - ft_wstr_len(str)))
				ret[i++] = ' ';
			while (str[j])
				ret[i++] = str[j++];
			ret[i] = '\0';
		}
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstr_len(str) + 1));
		while (str[j])
			ret[i++] = str[j++];
		ret[i] = '\0';
	}
	// free(str);
	return (ret);
}


wchar_t	*ft_make_wc(t_flags *flag, int c)
{
	wchar_t	*ret;
	int		n_cnt;

	n_cnt = 0;
	ft_checkflags(flag);

	// ft_putendl("making wide char");

	// REMEMBER TO COUNT +1 WHEN IT'S A NULL W_CHAR
	if (c)
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 2);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * 1);
		ret[0] = '\0';
		n_cnt = 1;
	}
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width - n_cnt, flag->minus);
	return (ret);
}


/*
** Making wstring from wstring!
*/

wchar_t	*ft_makepres_ws(wchar_t *str, int pres)
{
	wchar_t	*ret;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (pres < ft_wstr_len(str))
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (pres + 1));
		while (len < pres)
		{
			ret[i] = str[i];
			len += ft_wchar_len(ret[i]);
			i++;
		}
		ret[i] = '\0';
	}
	else
	{
		ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wstr_len(str) + 1));
		while (str[++i])
			ret[i] = str[i];
		ret[i] = '\0';
	}
	// ft_strdel(&str);
	return (ret);
}

wchar_t	*ft_make_wstr(t_flags *flag, wchar_t *str)
{
	wchar_t *ret;

	// ft_putendl("strings");
	// ret = (wchar_t *)malloc(sizeof(wchar_t) * (ft_strlen(str) + 1));
	// ret = ft_strncpy(ret, str, (ft_strlen(str) + 1));
	ret = str;
	ft_checkflags(flag);
	if (flag->precision)
		ret = ft_makepres_ws(ret, flag->precision);
	if (flag->f_width)
		ret = ft_makewide_ws(ret, flag->f_width, flag->minus);
	return (ret);
}


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



/* ********************************* **
**    Collecting data from va_arg    **
** ********************************* */

void	ft_getdata(t_flags *flag, va_list *arg, t_data *data)
{
	if ((flag->conv_i >= 0 && flag->conv_i <= 1) || (flag->conv_i >= 2 && flag->conv_i <= 5 && flag->lm == 0))
	{
		data->nb = va_arg(*arg, int);
		if (data->nb < 0 && (flag->conv == 'd' || flag->conv == 'D' || flag->conv == 'i'))
		{
			flag->plus = 1;
			flag->neg = 1;
			data->nb = -data->nb;
		}
		if (flag->conv_i >= 2 && data->nb < 0)
			data->nb = UINT_MAX + data->nb + 1;
	}

	else if ((flag->conv_i >= 2 && flag->conv_i <= 5) && flag->lm == 1)
	{
		data->nb = va_arg(*arg, int);
		if (data->nb < 0)
			data->nb = UCHAR_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 2 && flag->conv_i <= 5) && flag->lm == 2)
	{
		data->nb = va_arg(*arg, int);
		if (data->nb < 0)
			data->nb = USHRT_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 6 && flag->conv_i <= 8) || ((flag->conv_i >= 2 && flag->conv_i <= 5) && flag->lm == 3))
	{
		data->nb = va_arg(*arg, long);
		if (data->nb < 0)
			data->nb = ULONG_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 2 && flag->conv_i <= 5) && flag->lm == 4)
	{
		data->nb = va_arg(*arg, long long);
		if (data->nb < 0)
			data->nb = ULLONG_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 5)
	{
		data->nb = va_arg(*arg, intmax_t);
		if (data->nb < 0)
			data->nb = UINT_MAX + data->nb + 1;
	}
	else if ((flag->conv_i >= 0 && flag->conv_i <= 5) && flag->lm == 6)
	{
		data->nb = va_arg(*arg, size_t);
		if (data->nb < 0)
			data->nb = SIZE_MAX + data->nb + 1;
	}

	else if (flag->conv_i == 9 && flag->lm == 0)
		data->c = va_arg(*arg, int);
	else if ((flag->conv_i == 10 && flag->lm == 0) || (flag->conv_i == 9 && flag->lm == 3))
		data->w_chr = va_arg(*arg, wchar_t);			
	else if (flag->conv_i == 11 && flag->lm == 0)
		data->str = va_arg(*arg, char*);
	else if ((flag->conv_i == 12 && flag->lm == 0) || (flag->conv_i == 11 && flag->lm == 3))
		data->w_str = va_arg (*arg, wchar_t*);
	else if (flag->conv_i == 13)
		data->ptr = va_arg(*arg, void*);
}


int	ft_printf(const char * restrict format, ...)
{
	int			i;
	char		*found;
	char		*conv;
	char 		*tmp;
	va_list		arg;
	t_flags		flag;
	t_data		data;

	// ft_putstr("\n\n*** ft_printf ***\n");
	tmp = (char *)format;
	va_start(arg, format);
	i = 0;
	while (*tmp)
	{
		// ft_putstr("tmp here?\n");
		if (*tmp != '%')
			ft_putchar(*tmp);
		else if (*tmp == '%')
		{
			found = tmp;
			tmp++;
			if (*tmp == '%')
				ft_putchar(*tmp);
			else
			{
				conv = (char *)malloc(sizeof(char) * ft_clen(tmp) + 1);
				conv = ft_strncpy(conv, tmp, ft_clen(tmp));
				conv[ft_clen(tmp)] = '\0';
				// ft_putstr("\nconv: |");
				// ft_putstr(conv);
				// ft_putstr("|\n");

				ft_bzero(&flag, sizeof(t_flags));
				ft_bzero(&data, sizeof(t_data));
				// ft_putchar('\n');
				if (ft_parse(conv, &flag) == -1)
					return (-1);
				if (flag.fw_ast)
				{
					flag.f_width = va_arg(arg, int);
					flag.fw_ast = 0;
				}
				if (flag.p_ast)
				{
					flag.precision = va_arg(arg, int);
					flag.p_ast = 0;
				}
				ft_getdata(&flag, &arg, &data);

				if (flag.conv_i >= 0 && flag.conv_i <= 5)
					ft_putstr(ft_make_num(&flag, data.nb));
				else if (flag.conv_i == 9 && flag.lm == 0)
					ft_putstr(ft_make_c(&flag, data.c));
				else if ((flag.conv_i == 10 && flag.lm == 0) || (flag.conv_i == 9 && flag.lm == 3))
					ft_putwstr(ft_make_wc(&flag, data.w_chr));
				else if (flag.conv_i == 11 && flag.lm == 0)
					ft_putstr(ft_make_s(&flag, data.str));
				else if ((flag.conv_i == 12 && flag.lm == 0) || (flag.conv_i == 11 && flag.lm == 3))
					ft_putwstr(ft_make_wstr(&flag, data.w_str));
				else if (flag.conv_i == 13)
				{
					// Pass void *
					// ft_putendl("void");
					// ft_putchar(flag.conv);
					// ft_putnbr(data.ptr);
					ft_putstr(ft_make_ptr(data.ptr));
				}
				else
					ft_putendl("else?");
				// ft_putstr("*** parsed ***\n");
				// ft_putflags(flag);
				tmp += (ft_clen(tmp) - 1);
				free(conv);
				conv = NULL;
			}
		}
		// ft_parse(conv);
		tmp++;
	}
	va_end(arg);
	return (i);
}
