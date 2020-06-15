/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/16 01:39:30 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*flag_numbersign(char *result, const char *format)
{
	char		*temp;

	if (ft_strchr(format, '#'))
	{
		temp = result;
		if (ft_strpbrk(format, "x"))
			result = (ft_strjoin("0x", result));
		else if (ft_strpbrk(format, "X"))
			result = (ft_strjoin("0X", result));
		if (temp != result)
			free(temp);
	}
	return (result);
}

char					*flag_plus_space(char *result, const char *format)
{
	char		*temp;

	temp = result;
	if (ft_strpbrk(format, "di"))
	{
		if (ft_strchr(format, '+'))
		{
			if (!ft_strchr(result, '-'))
				if (ft_strpbrk(result, "1234567890"))
					result = (ft_strjoin("+", result));
		}
		else if (ft_strchr(format, ' '))
			result = (ft_strjoin(" ", result));
	}
	if (temp != result)
		free(temp);
	return (result);
}
/*
char					*flags(char *result, const char *format)
{
	
	result = flag_numbersign(result, format);
	result = flag_plus_space(result, format);
	if (ft_memchr(*format, '-', flags_len))
		*(*temp)++ = '-';
	else if (ft_memchr(*format, '0', flags_len))
		*(*temp)++ = '0';
}
*/

char					*precision(char *result, const char *format)
{
	char		*p_start;
	char		*temp;
	int			precision;

	temp = result;
	result = ft_strpbrk(result, "1234567890");
	if (!(p_start = ft_strchr(format, '.')) ||
		(precision = ft_atoi(p_start + 1)) <= ft_strlen(result))
		return (result);
	if ((result = ft_calloc(precision + 1, sizeof(char))))
	{
		ft_memset(result, '0', precision);
		if (*temp == '-')
		{
			*result = '-';
			temp++;
		}
		ft_memcpy(result + (ft_strlen(result) - ft_strlen(temp)), temp, ft_strlen(temp));
		if (*result == '-')
			temp--;
	}
	free(temp);
	return (result);
}

char					*field_width(char *result, const char *format)
{
	char				*w_start;
	int					width;
	char				*temp;

	if (!(w_start = ft_strpbrk(format, "123456789")) ||
		(w_start - 1) == '.' ||
		(width = ft_atoi(w_start)) <= ft_strlen(result))
		return (result);
	temp = result;
	if ((result = ft_calloc(width + 1, sizeof(char))))
	{
		ft_memset(result, ' ', width);
		if (ft_strpbrk(format, "-"))
			ft_memcpy(result, temp, ft_strlen(temp));
		else
		{
			if ((*(ft_strpbrk(format, "1234567890")) == '0') &&
				ft_strpbrk(format, "di") &&
				!ft_strchr(format, '.'))
				ft_memset(result, '0', width);
			ft_memcpy(result + (ft_strlen(result) - ft_strlen(temp)), temp, ft_strlen(temp));
		}
	}
	free(temp);
	return (result);
}
