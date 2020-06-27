/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/27 20:20:29 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647

static char			*round_float(char *result)
{
	size_t			len;
	unsigned int	i;

	len = ft_strlen(result);
	i = 2;
	if (result[len - 1] >= '5')
	{
		i += result[len - i] == '.';
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
	if (precision == 0)
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
	result = addexp(result, exp);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}
