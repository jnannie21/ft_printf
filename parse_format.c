/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 01:53:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/14 03:31:53 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLAGS "-0# +"
#define FIELD_WIDTH "*1234567890"
#define PRECISON "1234567890"
#define LENGTH_MODIFIERS "lh"

static void				parse_flags(char **temp, const char **format)
{
	if (ft_strnstr(*format, "#", ft_strspn(*format, FLAGS)))
		*(*temp)++ = '#';
	if (ft_strnstr(*format, "+", ft_strspn(*format, FLAGS)))
		*(*temp)++ = '+';
	else if (ft_strnstr(*format, " ", ft_strspn(*format, FLAGS)))
		*(*temp)++ = ' ';
	if (ft_strnstr(*format, "-", ft_strspn(*format, FLAGS)))
		*(*temp)++ = '-';
	else if (ft_strnstr(*format, "0", ft_strspn(*format, FLAGS)))
		*(*temp)++ = '0';
	*format = *format + ft_strspn(*format, FLAGS);
}

static void				parse_width_and_prec(char **temp, const char **format)
{
	while (ft_strchr(FIELD_WIDTH, **format))
		*(*temp)++ = *(*format)++;
	if (**format == '.')
	{
		*(*temp)++ = *(*format)++;
		while (**format == '0')
			(*format)++;
		if (!ft_strchr(PRECISON, **format))
			*(*temp)++ = '0';
		while (ft_strchr(PRECISON, **format))
			*(*temp)++ = *(*format)++;
	}
}

char					*parse_format(const char **format)
{
	char		*result;
	char		*temp;
	size_t		format_len;

	temp = (char *)*format;
	*format = ft_strchrnul(*format, '%');
	if (*temp != '%')
		return (ft_substr(temp, 0, *format - temp));
	format_len = ft_strpbrk(*format + 1, CONVERSIONS) - *format;
	if (!(result = ft_calloc(format_len, sizeof(char))))
		return (0);
	temp = result;
	*temp++ = *(*format)++;
	parse_flags(&temp, format);
	parse_width_and_prec(&temp, format);
	if (ft_strspn(*format, LENGTH_MODIFIERS) > 2 ||
		(ft_strspn(*format, LENGTH_MODIFIERS) == 2 &&
		**format != *(*format + 1)))
		return (result);
	while (ft_strchr(LENGTH_MODIFIERS, **format))
		*temp++ = *(*format)++;
	*format = *format + ft_strspn(*format, LENGTH_MODIFIERS);
	if (ft_strchr(CONVERSIONS, **format))
		*temp = *(*format)++;
	return (result);
}
