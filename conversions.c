/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 17:15:36 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

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
	return (ft_itoa_base(read_signed_arg(args, format), 10));
}

static char					*strtolower(char *str)
{
	unsigned int		i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

char						*ft_convert_uxX(va_list args, const char *format)
{
	unsigned long long	arg;
	char				*last_digit;
	char				*result;
	char				*remains;
	int					base;

	arg = (unsigned long long)read_unsigned_arg(args, format);
	base = 10;
	if (ft_strpbrk(format, "xX"))
		base = 16;
	last_digit = ft_itoa_base(arg % base, base);
	if (arg / base != 0)
		remains = ft_itoa_base(arg / base, base);
	else
		remains = ft_strdup("");
	result = ft_strjoin(remains, last_digit);
	if (ft_strpbrk(format, "x"))
		strtolower(result);
	free(remains);
	free(last_digit);
	return (result);
}
/*
char						*ft_convert_c(va_list args, char *format)
{
	char		*result;

	(void *)format;
	result = ft_calloc(2, sizeof(char));
	result[0] = (unsigned char)va_arg(args, char);
	return (result);
}

char						*ft_convert_s(va_list args, char *format)
{
	char		*result;

	result = (char *)va_arg(args, char *);
	return (ft_strdup(result));
}

char						*ft_convert_percent(va_list args, char *format)
{
	return (ft_strdup("%"));
}

char						*ft_convert_pointer(va_list args, char *format)
{
	return (ft_convert_uxX(args, "llX"));
}
*/
