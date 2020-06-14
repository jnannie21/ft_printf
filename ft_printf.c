/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/14 20:14:03 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PRINTABLE 127

typedef char *(*conversion_func)(va_list ,const char *);

static conversion_func		*get_conversions(void)
{
	static conversion_func	conversions[PRINTABLE];

	if (!conversions['d'])
	{
		conversions['d'] = ft_convert_di;
		conversions['i'] = ft_convert_di;
		conversions['u'] = ft_convert_u;
		conversions['x'] = ft_convert_xX;
		conversions['X'] = ft_convert_xX;
		conversions['c'] = ft_convert_c;
		conversions['s'] = ft_convert_s;
		conversions['%'] = ft_convert_prcnt;
		conversions['p'] = ft_convert_ptr;
		conversions['n'] = ft_convert_n;
	}
	return (conversions);
}

static char					*get_output_by_format(va_list args, char *format)
{
	char				*conversion;
	char				*output;

	if (!format ||
		*format != '%' ||
		!(conversion = ft_strpbrk(format + 1, CONVERSIONS)))
		return ((char *)format);
	output = get_conversions()[(int)*conversion](args, format);
	free(format);
	return (output);
}

int							ft_printf(const char *format, ...)
{
	va_list		args;
	char		*output;

	va_start(args, format);
	while (*format)
	{
		if (!(output = get_output_by_format(args, parse_format(args, &format))))
			break ;
		write(1, output, ft_strlen(output));
		output_len(1, ft_strlen(output));
		free(output);
	}
	va_end(args);
	if (*format != '\0')
		return (-1);
	return (output_len(0, 0));
}
