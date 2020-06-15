/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/15 03:16:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char					*flag_numbersign(char *result, const char *format)
{
	if (ft_strpbrk(format, "x"))
		return (ft_strjoin("0x", result));
	return (ft_strjoin("0X", result));
}

static char					*flag_space(char *result)
{
	return (ft_strjoin(" ", result));
}

static char					*flag_plus(char *result)
{
	return (ft_strjoin("+", result));
}

char					*field_width(char *result, const char *format)
{
	char				*field_s;
	size_t				field_width;
	char				*padd;
	char				*temp;
	char				*temp2;

	if (!(field_s = ft_strpbrk(format, "123456789")))
		return (result);
	field_width = ft_atoi(field_s);
	if (field_width <= ft_strlen(result))
		return (result);
	if (!(padd = ft_calloc(field_width - ft_strlen(result) + 1, sizeof(char))))
		return (0);
	ft_memset(padd, ' ', field_width - ft_strlen(result));
	if (ft_strpbrk(format, "-"))
		result = ft_strjoin(result, padd);
	else
	{
		if (ft_strpbrk(format, "di") && ft_strpbrk(format, "0") &&
			(ft_strpbrk(format, "0") < ft_strpbrk(format, "123456789")))
		{
			ft_memset(padd, '0', field_width - ft_strlen(result));
			if (!ft_strchr("1234567890", *result))
			{
				if (!(temp = ft_substr(result, 0, 1)))
					return (0);
				result += 1;
				temp2 = padd;
				padd = ft_strjoin(temp, padd);
				free(temp);
				free(temp2);
				if (!padd)
					return (0);
			}
		}
		result = ft_strjoin(padd, result);
	}
	free(padd);
	return (result);
}
