/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/02 15:11:06 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			read_signed_arg(t_format *sf)
{
	if (sf->len_mod == 2 * 'l')
		return (long long)(va_arg(sf->args, long long));
	else if (sf->len_mod == 'l')
		return (long)(va_arg(sf->args, long));
	else if (sf->len_mod == 2 * 'h')
		return (char)(va_arg(sf->args, int));
	else if (sf->len_mod == 'h')
		return (short)(va_arg(sf->args, int));
	else
		return (int)(va_arg(sf->args, int));
}

unsigned long long	read_unsigned_arg(t_format *sf)
{
	if (sf->len_mod == 2 * 'l')
		return ((unsigned long long)va_arg(sf->args, long long));
	else if (sf->len_mod == 'l')
		return ((unsigned long)va_arg(sf->args, long));
	else if (sf->len_mod == 2 * 'h')
		return ((unsigned char)va_arg(sf->args, int));
	else if (sf->len_mod == 'h')
		return ((unsigned short)va_arg(sf->args, int));
	else
		return ((unsigned int)va_arg(sf->args, int));
}

int						ft_convert_di(t_format *sf)
{
	char				*result;
	long long			arg;

	arg = read_signed_arg(sf);
	result = ft_itoa_base(arg, 10);
	result = integer_precision(result, sf);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int						ft_convert_u(t_format *sf)
{
	char				*result;

	result = u_itoa_base(read_unsigned_arg(sf), 10);
	result = integer_precision(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	result = flag_zero(result, sf);
	return (print_result(result, sf));
}

int						ft_convert_xX(t_format *sf)
{
	char				*result;
	long long			arg;

	arg = read_unsigned_arg(sf);
	result = u_itoa_base(arg, 16);
	if (result && sf->conversion == 'x')
		strtolower(result);
	result = integer_precision(result, sf);
	if (arg != 0)
		result = flag_alter_i(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	result = flag_zero(result, sf);
	return (print_result(result, sf));
}
