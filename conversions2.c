/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:01:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/01 11:39:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define UTF8_MAX_OCTETS 4

char						*ft_convert_c(va_list args, const char *format)
{
	char		*result;
	wint_t		wc;

	wc = (wint_t)va_arg(args, wint_t);
	if (ft_strnstr(format, "l", ft_strlen(format)))
	{
		if ((result = ft_calloc(UTF8_MAX_OCTETS + 1, sizeof(char))))
			ft_wctomb(result, wc);
	}
	else
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = (unsigned char)wc;
	}
	result = width(result, format);
	result = flag_minus(result, format);
	return (result);
}

char						*ft_convert_s(va_list args, const char *format)
{
	char		*result;

	if (!(result = (char *)va_arg(args, char *)))
	{
		result = ft_strdup("(null)");
		if (read_precision(format) < 6)
			*result = '\0';
	}
	else
		result = ft_strdup(result);
	result = string_precision(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	return (result);
}

char						*ft_convert_prcnt(va_list args, const char *format)
{
	char	*result;

	if (!args || !format)
		return (0);
	result = ft_strdup("%");
	return (result);
}

char						*ft_convert_ptr(va_list args, const char *format)
{
	char				*result;
	long long			arg;

	arg = read_unsigned_arg(args, "ll");
	if (arg == 0)
	{
		result  = ft_strdup("(nil)");
		result = width(result, format);
		result = flag_minus(result, format);
		return (result);
	}
	if ((result = u_itoa_base(arg, 16)))
		strtolower(result);
	result = integer_precision(result, format);
	if (arg != 0)
		result = flag_numbersign_i(result, "#x");
	result = flag_plus_space(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

char						*ft_convert_n(va_list args, const char *format)
{
	void		*ptr;

	ptr = ((void *)va_arg(args, void *));
	if (ft_strnstr(format, "ll", ft_strlen(format)))
		*((long long *)ptr) = output_len(0, 0);
	else if (ft_strnstr(format, "l", ft_strlen(format)))
		*((long *)ptr) = output_len(0, 0);
	else if (ft_strnstr(format, "hh", ft_strlen(format)))
		*((char *)ptr) = output_len(0, 0);
	else if (ft_strnstr(format, "h", ft_strlen(format)))
		*((short int *)ptr) = output_len(0, 0);
	else
		*((int *)ptr) = output_len(0, 0);
	return (ft_strdup(""));
}