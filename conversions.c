/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/09 17:32:41 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <wchar.h>

#define UTF8_MAX_OCTETS 4

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
	result = 0;
	if (last_digit && remains)
		result = ft_strjoin(remains, last_digit);
	free(remains);
	free(last_digit);
	if (result && ft_strpbrk(format, "x"))
		strtolower(result);
	return (result);
}

char						*ft_convert_c(va_list args, const char *format)
{
	char		*result;
	wint_t		wc;

	wc = (wint_t)va_arg(args, wint_t);
	if (ft_strnstr(format, "l", ft_strlen(format)))
	{
		result = ft_calloc(UTF8_MAX_OCTETS + 1, sizeof(char));
		ft_wctomb(result, wc);
	}
	else
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = (unsigned char)wc;
	}
	return (result);
}

char						*ft_convert_s(va_list args, const char *format)
{
	char		*result;

	if (ft_strnstr(format, "l", ft_strlen(format)))
		return (0);
	result = (char *)va_arg(args, char *);
	return (ft_strdup(result));
}
char						*ft_convert_prcnt(va_list args, const char *format)
{
	if (!args || !format)
		return (0);
	return (ft_strdup("%"));
}

char						*ft_convert_ptr(va_list args, const char *format)
{
	if (!args || !format)
		return (0);
	return (ft_convert_uxX(args, "llx"));
}

size_t						ft_printf_count_len(int set_zero, size_t l)
{
	static size_t		len;
	size_t				temp;

	len += l;
	temp = len;
	if (set_zero)
		len = 0;
	return (temp);
}

char						*ft_convert_n(va_list args, const char *format)
{
	void		*ptr;

	ptr = ((void *)va_arg(args, void *));
	if (ft_strnstr(format, "ll", ft_strlen(format)))
		*((long long *)ptr) = ft_printf_count_len(0, 0);
	else if (ft_strnstr(format, "l", ft_strlen(format)))
		*((long *)ptr) = ft_printf_count_len(0, 0);
	else if (ft_strnstr(format, "hh", ft_strlen(format)))
		*((char *)ptr) = ft_printf_count_len(0, 0);
	else if (ft_strnstr(format, "h", ft_strlen(format)))
		*((short int *)ptr) = ft_printf_count_len(0, 0);
	else
		*((int *)ptr) = ft_printf_count_len(0, 0);
	return (ft_strdup(""));
}