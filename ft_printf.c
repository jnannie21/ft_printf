/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 21:49:02 by jnannie          ###   ########.fr       */
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

static int					free_mem(t_list *output, char *substr, char *form_arg, size_t len)
{
	free(substr);
	free(form_arg);
	ft_lstclear(&output, free);
	free(get_conversions());
	return (len);
}

static char					*formatted_arg(va_list args, const char *format)
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
	t_list		*output;
	t_list		*new_el;
	char		*substr;
	char		*form_arg;

	va_start(args, format);
	output = 0;
	while (*format != '\0')
	{
		form_arg = 0;
		substr = 0;
		if (!(substr = get_substr(format)) ||
			(*substr == '%' && !(form_arg = formatted_arg(args, substr))) ||
			(*substr == '%' && !(new_el = ft_lstnew(form_arg))) ||
			(*substr != '%' && !(new_el = ft_lstnew(substr))))
			break ;
		ft_lstadd_back(&output, new_el);
		format += ft_strlen(substr);
		form_arg ? free(substr) : 0;
	}
	va_end(args);
	if (*format != '\0')
		return (free_mem(output, substr, form_arg, 0));
	return (free_mem(output, 0, 0, print_output(output)));
}
