/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/06 12:01:46 by jnannie          ###   ########.fr       */
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
	return (conversions);
}

static void					free_mem(char *output, char *cut)
{
	if (cut != output)
		free(cut);
	free(output);
	free(get_conversions());
}

static char					*format_arg(va_list args, const char *format)
{
	char				*conversion;

	if (!(conversion = ft_strpbrk(format + 1, CONVERSIONS)))
		return (0);
	return (get_conversions()[(int)(*conversion)](args, format));
}

static char					*get_substr(const char *format)
{
	char		*substr;
	char		*conversion;
	
	if (*format == '%')
	{
		if (!(conversion = ft_strpbrk(format + 1, CONVERSIONS)) ||
			!(substr = ft_substr(format, 0, conversion + 1 - format)))
			return (0);
		return (substr);
	}
	if (!ft_strpbrk(format, "%"))
		return (ft_strdup(format));
	return (ft_substr(format, 0, ft_strpbrk(format, "%") - format));
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
		if (!cut ||
			(*cut == '%' && !(output = format_arg(args, cut))))
			break ;
		ft_putstr_fd(output, 1);
		len += ft_strlen(output);
		format += ft_strlen(cut);
		free_mem(output, cut);
	}
	va_end(args);
	if (*format != '\0')
		free_mem(output, cut);
	return (len);
}
