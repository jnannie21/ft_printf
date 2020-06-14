/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 01:53:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/15 00:51:46 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLAGS "-0# +"
#define FIELD_WIDTH "1234567890"
#define PRECISON "1234567890"
#define LENGTH_MODIFIERS "lh"
#define MEMORY_FOR_INTS 19

static void				parse_flags(char **temp, const char **format)
{
	size_t		flags_len;

	flags_len = ft_strspn(*format, FLAGS);
	if (ft_memchr(*format, '#', flags_len))
		*(*temp)++ = '#';
	if (ft_memchr(*format, '+', flags_len))
		*(*temp)++ = '+';
	else if (ft_memchr(*format, ' ', flags_len))
		*(*temp)++ = ' ';
	if (ft_memchr(*format, '-', flags_len))
		*(*temp)++ = '-';
	else if (ft_memchr(*format, '0', flags_len))
		*(*temp)++ = '0';
	*format = *format + flags_len;
}

static int				read_from_argument(va_list args, char **temp,
													const char **format)
{
	char		*s_arg;
	int			i_arg;

	i_arg = (int)(va_arg(args, int));
	if (i_arg < 0 && (*(*format - 1)) == '.')
	{
		(*format)++;
		return (0);
	}
	else if ((*(*format - 1)) == '.')
		*(*temp)++ = '.';
	if (!(s_arg = ft_itoa(i_arg)))
		return (-1);
	ft_memcpy(*temp, s_arg, ft_strlen(s_arg));
	*temp = *temp + ft_strlen(s_arg);
	free(s_arg);
	(*format)++;
	return (0);
}

static int				parse_width_precision(va_list args, char **temp,
													const char **format)
{
	if (**format != '*')
		while (ft_strchr(FIELD_WIDTH, **format))
			*(*temp)++ = *(*format)++;
	else if (read_from_argument(args, temp, format) == -1)
		return (-1);
	if (**format == '.')
	{
		(*format)++;
		if (**format != '*')
		{
			while (**format == '0')
				(*format)++;
			if (!ft_strchr(PRECISON, **format))
				*(*temp)++ = '0';
			while (ft_strchr(PRECISON, **format))
				*(*temp)++ = *(*format)++;
		}
		else if (read_from_argument(args, temp, format) == -1)
			return (-1);
	}
	return (0);
}

static void				parse_len_conversion(char **temp, const char **format)
{
	if (ft_strspn(*format, LENGTH_MODIFIERS) > 2 ||
		(ft_strspn(*format, LENGTH_MODIFIERS) == 2 &&
		**format != *(*format + 1)))
		return ;
	while (ft_strchr(LENGTH_MODIFIERS, **format))
		*(*temp)++ = *(*format)++;
	if (ft_strchr(CONVERSIONS, **format))
		**temp = *(*format)++;
}

char					*parse_format(va_list args, const char **format)
{
	char		*result;
	char		*temp;
	size_t		format_len;

	temp = (char *)*format;
	*format = ft_strchrnul(*format, '%');
	if (*temp != '%')
		return (ft_substr(temp, 0, *format - temp));
	if ((temp = ft_strpbrk(*format + 1, CONVERSIONS)))
		format_len = temp - *format + 1;
	else
		format_len = ft_strlen(*format);
	if (!(result = ft_calloc(format_len + MEMORY_FOR_INTS + 1, sizeof(char))))
		return (0);
	temp = result;
	*temp++ = *(*format)++;
	parse_flags(&temp, format);
	if (parse_width_precision(args, &temp, format) == -1)
	{
		free(result);
		return (0);
	}
	parse_len_conversion(&temp, format);
	return (result);
}
