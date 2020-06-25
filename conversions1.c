/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/25 11:13:08 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			read_signed_arg(va_list args, const char *format)
{
	if (ft_strnstr(format, "ll", ft_strlen(format)))
		return (long long)(va_arg(args, long long));
	else if (ft_strnstr(format, "l", ft_strlen(format)))
		return (long)(va_arg(args, long));
	else if (ft_strnstr(format, "hh", ft_strlen(format)))
		return (char)(va_arg(args, int));
	else if (ft_strnstr(format, "h", ft_strlen(format)))
		return (short)(va_arg(args, int));
	else
		return (int)(va_arg(args, int));
}

unsigned long long	read_unsigned_arg(va_list args, const char *format)
{
	if (ft_strnstr(format, "ll", ft_strlen(format)))
		return ((unsigned long long)va_arg(args, long long));
	else if (ft_strnstr(format, "l", ft_strlen(format)))
		return ((unsigned long)va_arg(args, long));
	else if (ft_strnstr(format, "hh", ft_strlen(format)))
		return ((unsigned char)va_arg(args, int));
	else if (ft_strnstr(format, "h", ft_strlen(format)))
		return ((unsigned short)va_arg(args, int));
	else
		return ((unsigned int)va_arg(args, int));
}

char						*ft_convert_di(va_list args, const char *format)
{
	char				*result;
	long long			arg;

	arg = read_signed_arg(args, format);
	result = ft_itoa_base(arg, 10);
	result = integer_precision(result, format);
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

char						*ft_convert_u(va_list args, const char *format)
{
	char				*result;

	result = u_itoa_base(read_unsigned_arg(args, format), 10);
	result = integer_precision(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	result = flag_zero(result, format);
	return (result);
}

char						*ft_convert_xX(va_list args, const char *format)
{
	char				*result;
	long long			arg;

	arg = read_unsigned_arg(args, format);
	result = u_itoa_base(arg, 16);
	if (result && ft_strpbrk(format, "x"))
		strtolower(result);
	result = integer_precision(result, format);
	if (arg != 0)
		result = flag_numbersign_i(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	result = flag_zero(result, format);
	return (result);
}
