/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_format1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 02:58:46 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 23:35:52 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_ft_printf.h"

char			*width(char *result, t_format *sf)
{
	if (!result)
		return (0);
	if (!sf->width)
		return (result);
	result = ft_fill_in(result, 0, sf->width, ' ');
	return (result);
}

char			*flag_plus_space(char *result, t_format *sf)
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

char			*flag_minus(char *result, t_format *sf)
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

char			*flag_zero(char *result, t_format *sf)
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
		result = ft_fill_in(result, prefix_len, ft_strlen(temp), '0');
		free(temp);
	}
	return (result);
}

char			*flag_space(char *result, t_format *sf)
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
