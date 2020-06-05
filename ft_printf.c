/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 13:11:38 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PRINTABLE 127

typedef char *(*conversion_func)(va_list ,char *);

static conversion_func		*get_conversions(void)
{
	static conversion_func	*conversions;

	if (conversions)
		return (conversions);
	if (!(conversions = malloc(PRINTABLE * sizeof(conversion_func))))
		return (0);
	conversions['d'] = ft_convert_integer;
	conversions['i'] = ft_convert_integer;
	return (conversions);
}

static int					free_mem(t_list *output, char *substr, size_t len)
{
	if (substr)
		free(substr);
	ft_lstclear(&output, free);
	if (get_conversions())
		free(get_conversions());
	return (len);
}

static char					*get_formatted_arg(va_list args, const char *format)
{
	char				*conversion;
	char				*substr;
	char				*temp;

	if (!(conversion = ft_strpbrk(format, CONVERSIONS)) ||
		!(substr = ft_substr(format, 0, conversion + 1 - format)))
		return (0);
	temp = substr;
	substr = get_conversions()[(int)(*conversion)](args, substr);
	free(temp);
	return (substr);
}

static char					*get_str(const char *format)
{
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

	va_start(args, format);
	substr = 0;
	output = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			if (!(substr = get_formatted_arg(args, format)))
				break ;
		}
		else if (!(substr = get_str(format)))
			break ;
		if (!(new_el = ft_lstnew(substr)))
			break ;
		ft_lstadd_back(&output, new_el);
		format = format + ft_strlen(substr) - ((*format == '%') ? 0 : 1);
	}
	va_end(args);
	if (*format != '\0')
		return (free_mem(output, substr, 0));
	return (free_mem(output, substr, print_output(output)));
}
