/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/09 18:59:54 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PRINTABLE 127
#define CONVERSIONS "cspdiuxX%nfge"
#define FORMAT_CH "-0.*lh# +cspdiuxX%nfge"

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

static int					free_mem(char *output, char *cut, int err)
{
	if (cut != output)
		free(cut);
	free(output);
	return (err);
}

static char					*format_arg(va_list args, const char *format)
{
	char				*conversion;

	if (!(conversion = ft_strpbrk(format + 1, CONVERSIONS)))
		return ((char *)format);
	return (get_conversions()[(int)*conversion](args, format));
}

static char					*get_substr(const char *format)
{
	char		*find;

	if (*format == '%')
	{
		if (!(find = ft_strpbrk(format + 1, CONVERSIONS)))
			return (ft_strdup(format));
		else if (ft_strspn(format, FORMAT_CH) < (size_t)(find - format))
			return (ft_substr(format, 0, ft_strspn(format, FORMAT_CH) + 1));
		else
			return (ft_substr(format, 0, find - format + 1));
	}
	if (!(find = ft_strpbrk(format, "%")))
		return (ft_strdup(format));
	return (ft_substr(format, 0, find - format));
}

int							ft_printf(const char *format, ...)
{
	va_list		args;
	char		*output;
	char		*cut;

	va_start(args, format);
	while (*format != '\0')
	{
		cut = get_substr(format);
		output = cut;
		if (!output ||
			(*output == '%' && !(output = format_arg(args, output))))
			break ;
		ft_putstr_fd(output, 1);
		ft_printf_count_len(0, ft_strlen(output));
		format += ft_strlen(cut);
		free_mem(output, cut, 0);
	}
	va_end(args);
	if (*format != '\0')
		return (free_mem(output, cut, -1));
	return (ft_printf_count_len(1, 0));
}
