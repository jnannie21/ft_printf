/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/07 16:13:40 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PRINTABLE 127

typedef char *(*conversion_func)(va_list ,const char *);

static conversion_func		*get_conversions(void)
{
	static conversion_func	*conversions;

	if (conversions)
		return (conversions);
	if (!(conversions = malloc(PRINTABLE * sizeof(conversion_func))))
		return (0);
	conversions['d'] = ft_convert_di;
	conversions['i'] = ft_convert_di;
	conversions['u'] = ft_convert_uxX;
	conversions['x'] = ft_convert_uxX;
	conversions['X'] = ft_convert_uxX;
	conversions['c'] = ft_convert_c;
	return (conversions);
}

static void					free_mem(char *output, char *cut)
{
	if (cut != output)
		free(cut);
	free(output);
}

static char					*format_arg(va_list args, const char *format)
{
	char				*conversion;

	if (!(conversion = ft_strpbrk(format + 1, CONVERSIONS)))
		return ((char *)format);
	return (get_conversions()[(int)(*conversion)](args, format));
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
	size_t		len;

	va_start(args, format);
	len = 0;
	while (*format != '\0')
	{
		cut = get_substr(format);
		output = cut;
		if (!output ||
			(*output == '%' && !(output = format_arg(args, output))))
			break ;
		ft_putstr_fd(output, 1);
		len += ft_strlen(output);
		format += ft_strlen(cut);
		free_mem(output, cut);
	}
	va_end(args);
	if (*format != '\0')
		free_mem(output, cut);
	free(get_conversions());
	return (len);
}
