/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:01:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/02 17:39:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define UTF8_MAX_OCTETS 4

int						ft_convert_c(t_format *sf)
{
	char		*result;
	wint_t		wc;
	int			len;
	int			char_len;

	wc = (wint_t)va_arg(sf->args, wint_t);
	if (sf->len_mod == 'l')
	{
		if ((result = ft_calloc(UTF8_MAX_OCTETS + 1, sizeof(char))))
			ft_wctomb(result, wc);
	}
	else
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = (unsigned char)wc;
	}
	char_len = ft_strlen(result);
	result = width(result, sf);
	result = flag_minus(result, sf);
	if (!result)
		return (-1);
	len = ft_strlen(result);
	sf->len += len - char_len + 1;
	return (write(1, result, len + !char_len));
}

int						ft_convert_s(t_format *sf)
{
	char		*result;

	if (!(result = (char *)va_arg(sf->args, char *)))
	{
		result = ft_strdup("(null)");
		if (sf->precision < 6)
			*result = '\0';
	}
	else
		result = ft_strdup(result);
	result = string_precision(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	return (print_result(result, sf));
}

int						ft_convert_prcnt(t_format *sf)
{
	char	*result;

	result = ft_strdup("%");
	return (print_result(result, sf));
}

int						ft_convert_ptr(t_format *sf)
{
	char				*result;
	long long			arg;

	arg = read_unsigned_arg(sf);
	if (arg == 0)
	{
		result  = ft_strdup("(nil)");
		result = width(result, sf);
		result = flag_minus(result, sf);
		return (print_result(result, sf));
	}
	if ((result = u_itoa_base(arg, 16)))
		strtolower(result);
	result = integer_precision(result, sf);
	if (arg != 0)
		result = flag_alter_i(result, sf);
	result = flag_plus_space(result, sf);
	result = width(result, sf);
	result = flag_minus(result, sf);
	result = flag_zero(result, sf);
	result = flag_space(result, sf);
	return (print_result(result, sf));
}

int						ft_convert_n(t_format *sf)
{
	void		*ptr;

	ptr = ((void *)va_arg(sf->args, void *));
	if (sf->len_mod == 2 * 'l')
		*((long long *)ptr) = sf->len;
	else if (sf->len_mod == 'l')
		*((long *)ptr) = sf->len;
	else if (sf->len_mod == 2 * 'h')
		*((char *)ptr) = sf->len;
	else if (sf->len_mod == 'h')
		*((short int *)ptr) = sf->len;
	else
		*((int *)ptr) = sf->len;
	return (0);
}