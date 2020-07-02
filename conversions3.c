/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/02 16:24:56 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6

int				ft_convert_f(t_format *sf)
{
	char				*result;
	double				arg;

	arg = (double)(va_arg(sf->args, double));
	if (sf->precision < 0)
		sf->precision = DEFAULT_PRECISION;
	result = ftoa_with_precision(arg, sf->precision);
	if (!is_special_case(arg))
		result = flag_alter_f(result, sf);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	if (!is_special_case(arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int				ft_convert_e(t_format *sf)
{
	char				*result;
	double				arg;
	int					ex10;

	arg = (double)(va_arg(sf->args, double));
	if (sf->precision < 0)
		sf->precision = DEFAULT_PRECISION;
	ex10 = count_exp10(arg);
	result = ftoa_with_precision(arg / ft_pow10(ex10), sf->precision);
	if (!is_special_case(arg))
		result = flag_alter_f(result, sf);
	if (!is_special_case(arg))
		result = addexp(result, ex10);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	if (!is_special_case(arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int				ft_convert_g(t_format *sf)
{
	char				*result;
	double				arg;
	int					ex10;

	arg = (double)(va_arg(sf->args, double));
	if (sf->precision < 0)
		sf->precision = DEFAULT_PRECISION;
	if (!sf->precision)
		sf->precision++;
	result = ftoa_g_conversion(arg, sf);
	if (!is_special_case(arg))
		result = flag_alter_f(result, sf);
	ex10 = count_exp10(arg);
	if (is_exp_form(ex10, sf->precision))
		result = addexp(result, ex10);
	if (!sf->flagalter)
		result = remove_insignificant_zeros(result);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	if (!is_special_case(arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}
