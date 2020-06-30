/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/30 21:43:57 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>

# define CONVERSIONS "cspdiuxX%nfge"

int					ft_printf(const char *format, ...);
size_t				output_len(int set, size_t l);
char				*parse_format(va_list args, const char **format);

char				*ft_convert_di(va_list args, const char *format_str);
char				*ft_convert_u(va_list args, const char *format);
char				*ft_convert_xX(va_list args, const char *format);
char				*ft_convert_c(va_list args, const char *format);
char				*ft_convert_s(va_list args, const char *format);
char				*ft_convert_prcnt(va_list args, const char *format);
char				*ft_convert_ptr(va_list args, const char *format);
char				*ft_convert_n(va_list args, const char *format);
char				*ft_convert_f(va_list args, const char *format);
char				*ft_convert_e(va_list args, const char *format);
char				*ft_convert_g(va_list args, const char *format);

char				*strtolower(char *str);
char				*u_itoa_base(unsigned long long n, int base);
int					is_special_case(double d);
char				*attach_prefix(char *result, char *prefix);
int					count_exp10(double d);
char				*fill_in(char *result, int pos,
							unsigned int length, char filler);

char				*integer_precision(char *result, const char *format);
char				*string_precision(char *result, const char *format);
char				*width(char *result, const char *format);
char				*flag_numbersign_i(char *result, const char *format);
char				*flag_numbersign_f(char *result, const char *format);
char				*flag_plus_space(char *result, const char *format);
char				*flag_minus(char *result, const char *format);
char				*flag_zero(char *result, const char *format);
char				*flag_space(char *result, const char *format);

unsigned long long	read_unsigned_arg(va_list args, const char *format);
long long			read_signed_arg(va_list args, const char *format);

int					read_precision(const char *format);
double				round_float(double arg, int precision);
char				*ftoa_with_precision(double arg, const char *format);
char				*addexp(char *result, int pw10);
char				*remove_insignificant_zeros(char *result);
int					is_exp_form(double arg, const char *format);
int					g_precision(double arg, const char *format);
char				*ftoa_g_conversion(double arg, const char *format);


#endif
