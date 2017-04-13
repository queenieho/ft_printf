/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qho <qho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 12:52:29 by qho               #+#    #+#             */
/*   Updated: 2017/04/13 16:13:16 by qho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <wchar.h>
# include <locale.h>


# define CONV "diouxXDOUcCsSp%"
# define FLAGS "#0-+ "
# define BASE "0123456789ABCDEF"

typedef struct	s_flags
{
	int		hash;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		fw_ast;
	int		f_width;
	int		p_ast;
	int		precision;
	int		lm;
	char	conv;
	int		conv_i;
	int		neg;
	int		x_pres;
}				t_flags;

typedef struct	s_data
{
	long long	nb;
	char		c;
	wchar_t		w_chr;
	char		*str;
	wchar_t		*w_str;
	void		*ptr; 
}				t_data;

typedef struct	s_format
{
	int			cnt;
	char		*found;
	char		*conv;
	char 		*tmp;
}				t_format;

void	ft_putchar_pf(char c, int *cnt);
void	ft_putstr_pf(char const *s, int *cnt);
void	ft_putwchar_pf(wchar_t c, int *cnt);
void	ft_putwstr_pf(wchar_t *str, int *cnt);

void	ft_putchar(char c);
void	ft_putstr(char const *s);
void	ft_putnbr(long long nb);

void	ft_putwchar(wchar_t c);
void	ft_putwstr(wchar_t *str);

void	ft_putflags(t_flags flag);
void	ft_putendl(char const *s);

void	ft_error(char *str);

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s1);
void	ft_strdel(char **str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *dst, char const *src, size_t len);
int		ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);

/*
** 		parse functions
*/

int		ft_parseflags(char *str, t_flags *flag);
int		ft_getwidth(char **str, t_flags *flag);
int		ft_getpres(char **str, t_flags *flag);
void	ft_parsenums(char **str, t_flags *flag);
int		ft_parseconv(char c);
void	ft_parselenmod(char **str, t_flags *flag);
int		ft_parse(char *str, t_flags *flag);
int		ft_clen(char *str); //conversion lenght?

void	ft_checkflags(t_flags *flag, unsigned long long nb);

char	*ft_makewide02(char *str, int width, int left);
char	*ft_makewide(char *str, int width, int left);
char	*ft_makepres02(char *str, int j, int pres);
char	*ft_makepres(char *str, int pres, int x_flag);


int		ft_tolower(int c);
char	*ft_changecase(char *str);
int		ft_countspace(char *str);
char	ft_addsign(t_flags *flag, int neg);
char	*ft_modnum011(char *str, t_flags *flag, int neg);
char	*ft_modnum01(char *str, t_flags *flag, int neg, int sp);
char	*ft_modnum022(char *str);
char	*ft_modnum021(char *str);
char	*ft_modnum02(char *str, int sp);
char	*ft_modnum03(char *str);
char	*ft_modnum(char *str, t_flags *flag, int neg);

char	*ft_make_num(t_flags *flag, unsigned long long nb);
char	*ft_itoa_base(unsigned long long value, int base);

char	*ft_make_c(t_flags *flag, int c, int *cnt);

char	*ft_makepres_s(char *str, int pres);
char	*ft_make_s(t_flags *flag, char *str);

int		ft_wchar_len(wchar_t c);
int		ft_wstr_len(const wchar_t *ws);
wchar_t	*ft_makewide_ws(wchar_t *str, int width, int left);
wchar_t	*ft_make_wc(t_flags *flag, int c, int *cnt);
wchar_t	*ft_makepres_ws(wchar_t *str, int pres);
wchar_t	*ft_make_wstr(t_flags *flag, wchar_t *str);
char	*ft_addhex(char *str);
char	*ft_make_ptr(void *nb);


void	ft_getshrtlong(t_flags *flag, va_list *arg, t_data *data);
void	ft_getllong(t_flags *flag, va_list *arg, t_data *data);
void	ft_getnumber(t_flags *flag, va_list *arg, t_data *data);
void	ft_getdata(t_flags *flag, va_list *arg, t_data *data);

int		ft_printf(const char * restrict format, ...);

#endif
