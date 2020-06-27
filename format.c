/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/27 18:54:46 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//#define HEX_DIGITS "0123456789abcdefABCDEF"
#define PREFIXES "0+-xX"

char					*integer_precision(char *result, const char *format)
{
	char				*precision_point;
	int					precision;
	int					negative;
	int					prefix_len;

	if (!result)
		return (0);
	negative = (*result == '-');
	if (!(precision_point = ft_strchr(format, '.')))
		return (result);
	precision = ft_atoi(precision_point + 1);
	if (precision == 0 && *result == '0')
	{
		free(result);
		result = ft_strdup("");
	}
	prefix_len = ft_strspn(result, PREFIXES);
	result = fill_in(result, prefix_len, precision + negative, '0');
	return (result);
}

char					*string_precision(char *result, const char *format)
{
	char				*precision_point;
	size_t				precision;
	size_t				len;

	if (!result)
		return (0);
	if (!(precision_point = ft_strchr(format, '.')))
		return (result);
	precision = ft_atoi(precision_point + 1);
	len = ft_strlen(result);
	if (precision < len)
		ft_memset(result + precision, '\0', len - precision);
	return (result);
}
/*
char					*double_precision(char *result, const char *format)
{
	char				*precision_point;
	size_t				precision;

	if (!result)
		return (0);
	if (!(precision_point = ft_strchr(format, '.')))
		return (result);
	precision = ft_atoi(precision_point + 1);
	result = fill_in(result, precision, PREFIXES, '0');
	return (result);
}
*/
char					*width(char *result, const char *format)
{
	char				*width_start;
	size_t				width;

	if (!result)
		return (0);
	if (!(width_start = ft_strpbrk(format, "123456789")) ||
		*(width_start - 1) == '.')
		return (result);
	width = ft_atoi(width_start);
	result = fill_in(result, 0, width, ' ');
	return (result);
}

char					*flag_plus_space(char *result, const char *format)
{
	char		*prefix;

	if (!result)
		return (0);
	prefix = ft_strdup("");
	if (*result == '-')
		return (result);
	if (ft_strchr(format, '+') ||
		ft_strchr(format, ' '))
		prefix = ft_strdup("+");
	return (ft_strjoin_wrap(prefix, result));
}

char					*flag_numbersign_i(char *result, const char *format)
{
	if (!result)
		return (0);
	if (ft_strchr(format, '#'))
	{
		if (ft_strpbrk(format, "x"))
			result = ft_strjoin_wrap(ft_strdup("0x"), result);
		else if (ft_strpbrk(format, "X"))
			result = ft_strjoin_wrap(ft_strdup("0X"), result);
	}
	return (result);
}

char					*flag_numbersign_f(char *result, const char *format)
{
	char		*temp;

	if (!result)
		return (0);
	if (!ft_strchr(format, '#') || ft_strchr(result, '.'))
		return (result);
	temp = ft_strjoin(result, ".");
	free(result);
	return (temp);
}

char					*flag_minus(char *result, const char *format)
{
	size_t		space_count;
	size_t		result_len;

	if (!result)
		return (0);
	if (ft_strchr(format, '-'))
	{
		space_count = ft_strspn(result, " ");
		result_len = ft_strlen(result + space_count);
		ft_memmove(result, result + space_count, result_len);
		ft_memset(result + result_len, ' ', space_count);
	}
	return (result);
}

char					*flag_zero(char *result, const char *format)
{
	char		*search;
	char		*temp;
	int			spaces;
	int			prefix_len;

	if (!result)
		return (0);
	if ((ft_strchr(format, '.') && ft_strpbrk(format, "diuxX")) ||
		ft_strchr(format, '-'))
		return (result);
	if ((search = ft_strpbrk(format, "1234567890")) &&
		*search == '0')
		{
			temp = result;
			spaces = ft_strspn(result, " ");
			result = ft_strdup(result + spaces);
			prefix_len = ft_strspn(result, PREFIXES);
			result = fill_in(result, prefix_len, ft_strlen(temp), '0');
			free(temp);
		}
	return (result);
}

char					*flag_space(char *result, const char *format)
{
	char		*sign;

	if (!result)
		return (0);
	if (ft_strchr(format, ' ') &&
		(sign = ft_strchr(result, '+')))
			*sign = ' ';
	return (result);
}
