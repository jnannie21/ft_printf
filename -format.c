/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/17 06:18:30 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define HEX_DIGITS "0123456789abcdefABCDEF"

static void					attach_spaces(char *result, size_t prefix_len)
{
	while (prefix_len--)
		if (*result == '0' && *(result + 1) != '\0')
			*result++ = ' ';
}

static char					*attach_prefix(char *result, char *prefix,
													const char *format)
{
	char		*temp;
	size_t		spaces_count;
	size_t		result_len;
	size_t		prefix_len;
	size_t		diff;

	prefix_len = ft_strlen(prefix);
	if (!ft_strchr(format, '.'))
		attach_spaces(result, prefix_len);
	spaces_count = ft_strspn(ft_strchrnul(result, ' '), " ");
	result_len = ft_strlen(result);
	diff = 0;
	if (spaces_count < prefix_len)
		diff = (prefix_len - spaces_count);
	temp = result;
	result = ft_calloc(result_len + diff + 1, sizeof(char));
	ft_memset(result, ' ', result_len + diff);
	if (*temp == ' ')
		ft_memcpy(result + diff, temp, result_len);
	else
		ft_memcpy(result + prefix_len, temp, result_len + diff - prefix_len);
	ft_memcpy(ft_strpbrk(result, HEX_DIGITS) - prefix_len, prefix, prefix_len);
	free(temp);
	return (result);
}

char					*flag_numbersign(char *result, const char *format)
{
	if (ft_strchr(format, '#'))
	{
		if (ft_strpbrk(format, "x"))
			result = attach_prefix(result, "0x", format);
		else if (ft_strpbrk(format, "X"))
			result = attach_prefix(result, "0X", format);
	}
	return (result);
}

char					*flag_plus_space(char *result, const char *format,
															long long arg)
{
	char		*prefix;

	prefix = "";
	if (arg < 0)
		prefix = "-";
	else if (ft_strchr(format, '+') && arg >= 0)
		prefix = "+";
	else if (ft_strchr(format, ' '))
		prefix = " ";
	return (attach_prefix(result, prefix, format));
}

char					*precision_width(char *result, const char *format)
{
	char				*number_start;
	size_t				number;
	char				*temp;
	char				filler;

	if (!(number_start = ft_strpbrk(format, "123456789")) ||
		(number = ft_atoi(number_start)) <= ft_strlen(result))
		return (result);
	filler = ' ';
	if (*(number_start - 1) == '.')
		filler = '0';
	temp = result;
	if ((result = ft_calloc(number + 1, sizeof(char))))
	{
		ft_memset(result, filler, number);
		ft_memcpy(result + (ft_strlen(result) - ft_strlen(temp)), temp, ft_strlen(temp));
	}
	free(temp);
	return (result);
}

char					*flag_minus_zero(char *result, const char *format)
{
	size_t		space_count;
	size_t		result_len;

	space_count = ft_strspn(result, " ");
	if (ft_strchr(format, '-'))
	{
		result_len = ft_strlen(result + space_count);
		ft_memmove(result, result + space_count, result_len);
		ft_memset(result + result_len, ' ', space_count);
	}
	else if (!(ft_strchr(format, '.')) &&
			ft_strpbrk(format, "1234567890") &&
			*(ft_strpbrk(format, "1234567890")) == '0')
		ft_memset(result, '0', space_count);
	return (result);
}
