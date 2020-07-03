/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/03 15:34:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define PREFIXES "0+-xX"

char					*integer_precision(char *result, t_format *sf)
{
	int					negative;
	int					prefix_len;

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
	result = fill_in(result, prefix_len, sf->precision + negative, '0');
	return (result);
}

char					*string_precision(char *result, t_format *sf)
{
	int				len;

	if (!result)
		return (0);
	if (sf->precision < 0)
		return (result);
	len = ft_strlen(result);
	if (sf->precision < len)
		*(result + sf->precision) = '\0';
	return (result);
}

char					*width(char *result, t_format *sf)
{
	if (!result)
		return (0);
	if (!sf->width)
		return (result);
	result = fill_in(result, 0, sf->width, ' ');
	return (result);
}

char					*flag_plus_space(char *result, t_format *sf)
{
	char		*prefix;

	if (!result)
		return (0);
	prefix = ft_strdup("");
	if (*result == '-')
		return (result);
	if (sf->flagplus ||
		sf->flagspace)
		prefix = ft_strdup("+");
	return (ft_strjoin_wrap(prefix, result));
}

char					*flag_alter_i(char *result, t_format *sf)
{
	if (!result)
		return (0);
	if (sf->flagalter|| sf->conversion == 'p')
	{
		if (sf->conversion == 'x' || sf->conversion == 'p')
			result = ft_strjoin_wrap(ft_strdup("0x"), result);
		else if (sf->conversion == 'X')
			result = ft_strjoin_wrap(ft_strdup("0X"), result);
	}
	return (result);
}

char					*flag_alter_f(char *result, t_format *sf)
{
	char		*temp;

	if (!result)
		return (0);
	if (!sf->flagalter || sf->precision > 0)
		return (result);
	temp = ft_strjoin(result, ".");
	free(result);
	return (temp);
}

char					*flag_minus(char *result, t_format *sf)
{
	size_t		space_count;
	size_t		result_len;

	if (!result)
		return (0);
	if (sf->flagminus)
	{
		space_count = ft_strspn(result, " ");
		result_len = ft_strlen(result + space_count);
		ft_memmove(result, result + space_count, result_len);
		ft_memset(result + result_len, ' ', space_count);
	}
	return (result);
}

char					*flag_zero(char *result, t_format *sf)
{
	char		*temp;
	int			spaces;
	int			prefix_len;

	if (!result)
		return (0);
	if ((sf->precision >= 0 && ft_strchr("diuxX", sf->conversion)) ||
		sf->flagminus)
		return (result);
	if (sf->flagzero)
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

char					*flag_space(char *result, t_format *sf)
{
	char		*sign;

	if (!result)
		return (0);
	if (sf->flagspace &&
		(sign = ft_strpbrk(result, "+-")) &&
		*sign == '+')
			*sign = ' ';
	return (result);
}
