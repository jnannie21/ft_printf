/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/26 07:33:56 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//#define HEX_DIGITS "0123456789abcdefABCDEF"
#define PREFIXES "0+-xX"

static void				strcpytoend(char *dest, const char *src)
{
	size_t		dest_len;
	size_t		src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	ft_memcpy(dest + dest_len - src_len, src, src_len);
}

static char				*fill_in(char *result, size_t length,
										char *prefixes, char filler)
{
	char	*temp;
	int		prefix_len;

	if (length <= ft_strlen(result))
		return (result);
	prefix_len = ft_strspn(result, prefixes);
	temp = result;
	if (!(result = ft_calloc(length + 1, sizeof(char))))
		return (0);
	ft_memset(result, filler, length);
	strcpytoend(result, temp + prefix_len);
	ft_memcpy(result, temp, prefix_len);
	free(temp);
	return (result);
}

char					*integer_precision(char *result, const char *format)
{
	char				*precision_point;
	int					precision;
	int					negative;

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
	result = fill_in(result, precision + negative, PREFIXES, '0');
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
	result = fill_in(result, width, "", ' ');
	return (result);
}

char					*flag_plus_space(char *result, const char *format)
{
	char		*prefix;

	if (!result)
		return (0);
	prefix = "";
	if (*result == '-')
		return (result);
	if (ft_strchr(format, '+') ||
		ft_strchr(format, ' '))
		prefix = "+";
	return (attach_prefix(result, prefix));
}

char					*flag_numbersign_i(char *result, const char *format)
{
	if (!result)
		return (0);
	if (ft_strchr(format, '#'))
	{
		if (ft_strpbrk(format, "x"))
			result = attach_prefix(result, "0x");
		else if (ft_strpbrk(format, "X"))
			result = attach_prefix(result, "0X");
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
			result = fill_in(result, ft_strlen(temp), PREFIXES, '0');
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
