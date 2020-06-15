/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:01:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/15 18:03:04 by jnannie          ###   ########.fr       */
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

	if (!args || !format)
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
	return (ft_convert_xX(args, "#llx"));
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