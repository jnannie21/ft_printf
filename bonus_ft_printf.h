/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_ft_printf.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/07 03:54:15 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_FT_PRINTF_H
# define BONUS_FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>

# define DEC_DIG "1234567890"
# define PREFIXES "0+-xX"
# define DEFAULT_FLOAT_PRECISION 6

typedef	struct		s_format
{
	char			*format;
	va_list			args;
	double			arg;
	int				ex10;
	int				precision;
	int				len;
	int				width;
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
int					ft_convert_xx(t_format *sf);
int					ft_convert_c(t_format *sf);
int					ft_convert_s(t_format *sf);
int					ft_convert_prcnt(t_format *sf);
int					ft_convert_ptr(t_format *sf);
int					ft_convert_n(t_format *sf);
int					ft_convert_f(t_format *sf);
int					ft_convert_e(t_format *sf);
int					ft_convert_g(t_format *sf);

int					print_result(char *result, t_format *sf);

char				*integer_precision(char *result, t_format *sf);
char				*string_precision(char *result, t_format *sf);
char				*width(char *result, t_format *sf);
char				*flag_alter_i(char *result, t_format *sf);
char				*flag_alter_f(char *result, t_format *sf);
char				*flag_plus_space(char *result, t_format *sf);
char				*flag_zero(char *result, t_format *sf);
char				*flag_space(char *result, t_format *sf);

unsigned long long	read_unsigned_arg(t_format *sf);
long long			read_signed_arg(t_format *sf);

int					read_precision(const char *format);
char				*addexp(char *result, int ex10);
char				*remove_insignificant_zeros(char *result);
double				prepare_arg(t_format *sf);
void				g_precision(t_format *sf);
char				*convert_c_length(t_format *sf);

#endif
