/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/04 14:23:16 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>

# define CONVERSIONS "cspdiuxX%nfge"
# define DEC_DIG "1234567890"

# define MINUS_ZERO 0x8000000000000000
# define POSITIVE_INFINITY 0x7FF0000000000000
# define NEGATIVE_INFINITY 0xFFF0000000000000
# define MIN_PNAN 0x7FF0000000000001
# define MAX_PNAN 0x7FFFFFFFFFFFFFFF
# define MIN_NNAN 0xFFF0000000000001
# define MAX_NNAN 0xFFFFFFFFFFFFFFFF

typedef	struct		s_format
{
	char			*format;
	va_list			args;
	int				len;
	int				width;
	int				precision;
	int				flagalter;
	int				flagplus;
	int				flagminus;
	int				flagzero;
	int				flagspace;
	int				len_mod;
	char			conversion;
}					t_format;

int					ft_printf(const char *format, ...);
void				parse_format(t_format *sf);

int					ft_convert_di(t_format *sf);
int					ft_convert_u(t_format *sf);
int					ft_convert_xX(t_format *sf);
int					ft_convert_c(t_format *sf);
int					ft_convert_s(t_format *sf);
int					ft_convert_prcnt(t_format *sf);
int					ft_convert_ptr(t_format *sf);
int					ft_convert_n(t_format *sf);
int					ft_convert_f(t_format *sf);
int					ft_convert_e(t_format *sf);
int					ft_convert_g(t_format *sf);

char				*strtolower(char *str);
char				*u_itoa_base(unsigned long long n, int base);
int					is_special_case(double d);
char				*attach_prefix(char *result, char *prefix);
int					count_exp10(double d);
char				*fill_in(char *result, int pos,
							unsigned int length, char filler);
int					print_result(char *result, t_format *sf);

char				*integer_precision(char *result, t_format *sf);
char				*string_precision(char *result, t_format *sf);
char				*width(char *result, t_format *sf);
char				*flag_alter_i(char *result, t_format *sf);
char				*flag_alter_f(char *result, t_format *sf);
char				*flag_plus_space(char *result, t_format *sf);
char				*flag_minus(char *result, t_format *sf);
char				*flag_zero(char *result, t_format *sf);
char				*flag_space(char *result, t_format *sf);

unsigned long long	read_unsigned_arg(t_format *sf);
long long			read_signed_arg(t_format *sf);

int					read_precision(const char *format);
double				round_float(double arg, int precision);
char				*convert_float(double arg, t_format *sf);
char				*addexp(char *result, int ex10);
char				*remove_insignificant_zeros(char *result);
int					is_exp_form(int ex10, int precision);
char				*ftoa_g_conversion(double arg, t_format *sf);
char				*ft_ftoa(double d, int precision);

#endif
