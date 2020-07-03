/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:32:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/03 14:39:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647

double			round_float(double arg, int precision)
{
//	long double			arg_pow;
//	long				argl;
	long double			del;
//	int					ex10;

//	ex10 = count_exp10(arg);
//	if (precision > 308 || (precision + ex10) > 307)
//	{
//		if (ex10 >= 0)
//			precision = 15 - ex10;
//		else
//			precision = 16;
//	}
	del = 0.5;
	if (arg < 0)
		del = -0.5;
	del /= ft_pow10(precision);
	arg += del;
//	argl = arg;
//	if ((int)((arg - argl) * 10) == 0)
//		arg = arg - (argl % 10) % 2;
	return (arg);
}

char			*convert_float(double arg, t_format *sf)
{
	char				*result;
	int					ex10;

	ex10 = count_exp10(arg);
	if (sf->conversion == 'e')
		arg = arg / ft_pow10(ex10);
	if (arg != 0)
		arg = round_float(arg, sf->precision);
	if (sf->conversion == 'e' &&
		count_exp10(arg) > 0)
		{
			ex10++;
			arg = arg / 10;
		}
	result = ft_ftoa(arg, sf->precision);
	if (!is_special_case(arg))
		result = flag_alter_f(result, sf);
	if (sf->conversion == 'e')
		result = addexp(result, ex10);
	return (result);
}

char			*addexp(char *result, int ex10)
{
	char		*strexp;

	strexp = ft_itoa(ex10);
	if (*strexp != '-')
		strexp = ft_strjoin_wrap(ft_strdup("+"), strexp);
	if (ex10 <= 9 && ex10 >= -9)
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

int			is_exp_form(int ex10, int precision)
{

	if (ex10 && (ex10 < -4 || ex10 >= precision))
		return (1);
	return (0);
}
/*
int			g_precision(int ex10, t_format *sf)
{

	return (sf->precision);
}
*/
char			*ftoa_g_conversion(double arg, t_format *sf)
{
	int					ex10;
	char				*result;

	ex10 = count_exp10(arg);
	if (is_exp_form(ex10, sf->precision))
	{
		sf->conversion = 'e';
		if (sf->precision)
			sf->precision--;
	}
	else 
		sf->precision = sf->precision - ex10 - 1;
	result = convert_float(arg, sf);
	return (result);
}