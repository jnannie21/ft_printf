/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/30 21:36:08 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char				*ft_convert_e(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					ex10;

	arg = (double)(va_arg(args, double));
	ex10 = count_exp10(arg);
	result = ftoa_with_precision(arg / ft_pow10(ex10), format);
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	if (!is_special_case(arg))
		result = addexp(result, ex10);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

char				*ft_convert_g(va_list args, const char *format)
{
	char				*result;
	double				arg;

	arg = (double)(va_arg(args, double));
	result = ftoa_g_conversion(arg, format);
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	if (is_exp_form(arg, format))
		result = addexp(result, count_exp10(arg));
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
