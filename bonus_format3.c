/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_format3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:44:55 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 23:35:59 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_ft_printf.h"

char			*integer_precision(char *result, t_format *sf)
{
	int			negative;
	int			prefix_len;

	if (!result)
		return (0);
	negative = (*result == '-');
	if (sf->precision < 0)
		return (result);
	if (sf->precision == 0 && *result == '0')
	{
		free(result);
		result = ft_strdup("");
	}
	prefix_len = ft_strspn(result, PREFIXES);
	result = ft_fill_in(result, prefix_len, sf->precision + negative, '0');
	return (result);
}

char			*flag_alter_i(char *result, t_format *sf)
{
	if (!result)
		return (0);
	if (sf->flagalter || sf->conversion == 'p')
	{
		if (sf->conversion == 'x' || sf->conversion == 'p')
			result = ft_strjoin_wrap(ft_strdup("0x"), result);
		else if (sf->conversion == 'X')
			result = ft_strjoin_wrap(ft_strdup("0X"), result);
	}
	return (result);
}

char			*string_precision(char *result, t_format *sf)
{
	int			len;

	if (!result)
		return (0);
	if (sf->precision < 0)
		return (result);
	len = ft_strlen(result);
	if (sf->precision < len)
		*(result + sf->precision) = '\0';
	return (result);
}
