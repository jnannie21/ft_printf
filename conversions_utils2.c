/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:32:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/30 21:35:37 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647

int			read_precision(const char *format)
{
	int					precision;
	char				*precision_point;

	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		precision = ft_atoi(precision_point + 1);
	return (precision);
}

double		round_float(double arg, int precision)
{
	double				arg_pow;
	long				argl;
	double				del;
	int					ex10;

	ex10 = count_exp10(arg);
	if (precision > 16 || (precision + ex10) > 15)
	{
		if (ex10 >= 0)
			precision = 15 - ex10;
		else
			precision = 16;
	}
	del = 0.5;
	if (arg < 0)
		del = -0.5;
	arg_pow = ft_pow10(precision);
	del = del / arg_pow;
	arg = arg + del;
	argl = arg;
	if (arg != (double)argl && (int)((arg - argl) * arg_pow * 10) == 0)
		arg = arg - ((int)((arg - argl) * arg_pow) % 2) / arg_pow;
	return (arg);
}

char			*ftoa_with_precision(double arg, const char *format)
{
	int					precision;
	char				*result;

	precision = read_precision(format);
	arg = round_float(arg, precision);
	result = ft_ftoa(arg, precision);
//	if (precision == 0 && ft_strchr(result, '.'))
//		*(ft_strchr(result, '.')) = '\0';
	return (result);
}

char			*addexp(char *result, int pw10)
{
	char		*strexp;

	strexp = ft_itoa(pw10);
	if (*strexp != '-')
		strexp = ft_strjoin_wrap(ft_strdup("+"), strexp);
	if (pw10 <= 9 && pw10 >= -9)
		strexp = fill_in(strexp, 1, ft_strlen(strexp) + 1, '0');
	result = ft_strjoin_wrap(result, ft_strdup("e"));
	result = ft_strjoin_wrap(result, strexp);
	return (result);
}

char			*remove_insignificant_zeros(char *result)
{
	char				*decimal_point;
	char				*temp1;
	char				*temp2;
	char				*last_zero;
	int					zeros;

	if (!(decimal_point = ft_strchr(result, '.')))
		return (result);
	last_zero = decimal_point + ft_strspn(decimal_point + 1, "0123456789");
	if (*last_zero != '0')
		return (result);
	zeros = 0;
	while (*(last_zero - zeros) == '0')
		zeros++;
	if (*(last_zero - zeros) == '.')
		zeros++;
	temp1 = ft_substr(result, 0, last_zero - zeros - result + 1);
	temp2 = result;
	result = ft_strjoin_wrap(temp1, ft_strdup(last_zero + 1));
	free(temp2);
	return (result);
}

int			is_exp_form(double arg, const char *format)
{
	int					precision;
	int					ex10;

	ex10 = count_exp10(arg);
	if (!(precision = read_precision(format)))
		precision++;
	if (ex10 && (ex10 < -4 || ex10 >= precision))
		return (1);
	return (0);
}

int			g_precision(double arg, const char *format)
{
	int					precision;
	int					ex10;

	if (!(precision = read_precision(format)))
		precision++;
	ex10 = count_exp10(arg);
	//if ((ex10 >= -4 && ex10 < precision))
	if (!is_exp_form(arg, format))
		precision = precision - ex10 - 1;
	else if (precision)
		precision--;
	return (precision);
}

char			*ftoa_g_conversion(double arg, const char *format)
{
	int					precision;
	int					ex10;
	char				*result;

	ex10 = count_exp10(arg);
	precision = g_precision(arg, format);
	if (is_exp_form(arg, format))
		arg = arg / ft_pow10(ex10);
	format = ft_strjoin_wrap(ft_strdup("."), ft_itoa(precision));
	result = ftoa_with_precision(arg, format);
	return (result);
}