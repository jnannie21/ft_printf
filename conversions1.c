/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/15 03:16:12 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long			read_signed_arg(va_list args, const char *format)
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

static unsigned long long	read_unsigned_arg(va_list args, const char *format)
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
	char				*temp;
	long long			arg;

	arg = read_signed_arg(args, format);
	if (!(result = ft_itoa_base(arg, 10)))
		return (0);
	temp = result;
	if (ft_strpbrk(format, "+") && arg >= 0)
		result = flag_plus(result);
	else if (ft_strpbrk(format, " ") && arg >= 0)
		result = flag_space(result);
	if (temp != result)
		free(temp);
	if (!result)
		return (0);
	temp = result;
	if (ft_strpbrk(format, "123456789"))
		result = field_width(result, format);
	if (temp != result)
		free(temp);
	if (!result)
		return (0);
	return (result);
}

char						*ft_convert_u(va_list args, const char *format)
{
	return (u_itoa_base(read_unsigned_arg(args, format), 10));
}

char						*ft_convert_xX(va_list args, const char *format)
{
	char				*result;
	char				*temp;

	if (!(result = u_itoa_base(read_unsigned_arg(args, format), 16)))
		return (0);
	if (ft_strpbrk(format, "x"))
		strtolower(result);
	if (ft_strpbrk(format, "#"))
	{
		temp = result;
		if (!(result = flag_numbersign(result, format)))
			return (0);
		free(temp);
	}
	return (result);
}
