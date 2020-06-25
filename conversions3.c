/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/25 15:12:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6

char						*ft_convert_f(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					precision;
	char				*precision_point;

	arg = (double)(va_arg(args, double));
	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		precision = ft_atoi(precision_point + 1);
	result = ft_ftoa(arg, precision);
	result = flag_plus_space(result, format);
	if (!double_is_special(arg))
		result = flag_numbersign_f(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!double_is_special(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}
