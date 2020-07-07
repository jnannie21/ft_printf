/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_conversions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/07 03:55:34 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_convert_f(t_format *sf)
{
	char				*result;

	sf->arg = (double)(va_arg(sf->args, double));
	if (sf->precision < 0)
		sf->precision = DEFAULT_FLOAT_PRECISION;
	sf->arg = prepare_arg(sf);
	result = ft_ftoa(sf->arg, sf->precision);
	if (!ft_is_double_special(sf->arg))
	{
		result = flag_alter_f(result, sf);
		if (sf->conversion == 'e')
			result = addexp(result, sf->ex10);
	}
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	if (!ft_is_double_special(sf->arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int				ft_convert_e(t_format *sf)
{
	char				*result;

	sf->arg = (double)(va_arg(sf->args, double));
	if (sf->precision < 0)
		sf->precision = DEFAULT_FLOAT_PRECISION;
	sf->arg = prepare_arg(sf);
	result = ft_ftoa(sf->arg, sf->precision);
	if (!ft_is_double_special(sf->arg))
	{
		result = flag_alter_f(result, sf);
		if (sf->conversion == 'e')
			result = addexp(result, sf->ex10);
	}
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	if (!ft_is_double_special(sf->arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int				ft_convert_g(t_format *sf)
{
	char				*result;

	sf->arg = (double)(va_arg(sf->args, double));
	g_precision(sf);
	sf->arg = prepare_arg(sf);
	result = ft_ftoa(sf->arg, sf->precision);
	if (!ft_is_double_special(sf->arg))
	{
		result = flag_alter_f(result, sf);
		if (sf->conversion == 'e')
			result = addexp(result, sf->ex10);
	}
	if (!sf->flagalter)
		result = remove_insignificant_zeros(result);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	if (!ft_is_double_special(sf->arg))
		result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}
