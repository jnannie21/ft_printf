/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/31 12:55:45 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ft_clear_memory(t_list *output, char *temp, char *substr, size_t len)
{
	if (temp)
		free(temp);
	if (substr)
		free(substr);
	ft_lstclear(&output, free);
	return (len);
}

static char			*ft_format_arg(va_list args, char *format_str)
{
	char		conversion;
	
	conversion = *(format_str + ft_strcspn(format_str, CONVERSIONS));
	if (!ft_strchr(CONVERSIONS, conversion))
		return (0);
	else if (ft_strchr(INTEGER_CONVERSIONS, conversion))
		return (ft_convert_integer(args, format_str));
	else if (ft_strchr(POINTER_CONVERSION, conversion))
		return (ft_convert_pointer(args, format_str));
	else if (ft_strchr(FLOAT_CONVERSIONS, conversion))
		return (ft_convert_pointer(args, format_str));
	else if (ft_strchr(CHAR_CONVERSION, conversion))
		return (ft_convert_char(args, format_str));
	else if (ft_strchr(STRING_CONVERSION, conversion))
		return (ft_convert_string(args, format_str));
	else if (ft_strchr(COUNT_CONVERSION, conversion))
		return (ft_convert_count(args, format_str));
	else if (ft_strchr(PERCENT_CONVERSION, conversion))
		return (ft_convert_percent(args, format_str));
}

int					ft_printf(const char *format, ...)
{
	va_list		args;
	t_list		*output;
	char		*substr;
	char		*temp;
	int			len;

	va_start(args, format);
	output = 0;
	while (*format != '\0')
	{
		len = ft_strcspn(format, (*format == '%' ? CONVERSIONS : "%"));
		if (!(temp = ft_substr(format, 0, len + (*format == '%' ? 1 : 0))) ||
			!(substr = (*format == '%' ? ft_format_arg(args, temp) : temp)))
			return (ft_clear_memory(output, temp, 0, 0));
		ft_lstadd_back(&output, ft_lstnew(substr));
		if (substr != temp)
			free(substr);
		free(temp);
		if (*(format + len) != '\0' && *format == '%')
			len++;
		format += len;
	}
	va_end(args);
	return (ft_clear_memory(output, 0, 0, ft_lstprint(output)));
}
