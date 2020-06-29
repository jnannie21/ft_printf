/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/29 15:17:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647
/*
static char			*count_len(char *result)
{
	size_t			len;
	char			*decimal_point;

	decimal_point = ft_strchr(result, '.');
	if (ft_strspn(decimal_point + 1, "0123456789") >= 16)
		len = decimal_point - result + 1 + 16;
	else
		len = ft_strlen(result);
	return (len);
}
*/
static char			*round_float(char *result)
{
	size_t			len;
	unsigned int	i;

	len = ft_strlen(result);
	i = 2 + result[len - 2] == '.';
	if (result[len - 1] > '5' ||
		(result[len - 1] == 5 && (result[len - i] - '0') % 2))
	{
		while (i <= len && result[len - i] == '9')
		{
			result[len - i] = '0';
			i++;
			i += result[len - i] == '.';
		}
		if (i <= len && ft_isdigit(result[len - i]))
			result[len - i]++;
		else
		{
			result = fill_in(result, (i == len), len + (i == len), '1');
			len++;
		}
	}
	result[len - 1] = '\0';
	return (result);
}

static char			*ftoa_with_precision(double arg, const char *format)
{
	int					precision;
	char				*precision_point;
	char				*result;

	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		precision = ft_atoi(precision_point + 1);
	result = ft_ftoa(arg, (precision == MAXINT) ? MAXINT : precision + 1);
	if (precision < MAXINT)
		result = round_float(result);
	if (precision == 0 && ft_strchr(result, '.'))
		*(ft_strchr(result, '.')) = '\0';
	return (result);
}

char				*ft_convert_f(va_list args, const char *format)
{
	char				*result;
	double				arg;

	arg = (double)(va_arg(args, double));
	result = ftoa_with_precision(arg, format);
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

static char			*addexp(char *result, int exp)
{
	char		*strexp;

	strexp = ft_itoa(exp);
	if (*strexp != '-')
		strexp = ft_strjoin_wrap(ft_strdup("+"), strexp);
	if (exp <= 9 && exp >= -9)
		strexp = fill_in(strexp, 1, ft_strlen(strexp) + 1, '0');
	result = ft_strjoin_wrap(result, ft_strdup("e"));
	result = ft_strjoin_wrap(result, strexp);
	return (result);
}

char				*ft_convert_e(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					exp;

	arg = (double)(va_arg(args, double));
	exp = count_exp10(arg);
	result = ftoa_with_precision(arg / ft_pow10(exp), format);
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	if (!is_special_case(arg))
		result = addexp(result, exp);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

static char			*remove_insignificant_zeros(char *result)
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

static int			replace_precision(int precision, int exp)
{
	if ((exp >= -4 && exp < precision))
		precision = precision - exp - 1;
	else if (precision)
		precision--;
	return (precision);
}

char				*ft_convert_g(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					exp;
	int					precision;
	char				*precision_point;

	arg = (double)(va_arg(args, double));
	exp = count_exp10(arg);
	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		if (!(precision = ft_atoi(precision_point + 1)))
			precision++;
	if (exp && (exp < -4 || exp >= precision))
		arg = arg / ft_pow10(exp);
	result = ftoa_with_precision(arg, ft_strjoin_wrap(ft_strdup("."), ft_itoa(replace_precision(precision, exp))));
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	if (exp && (exp < -4 || exp >= precision))
		result = addexp(result, exp);
	if (!ft_strchr(format, '#'))
		result = remove_insignificant_zeros(result);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}
