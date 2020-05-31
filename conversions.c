/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 12:03:30 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/31 14:43:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*ft_convert_integer(va_list args, char *format_str)
{
	long long	arg;
	char		conversion;

	conversion = *(format_str + ft_strcspn(format_str, INTEGER_CONVERSIONS));
	if (ft_strnstr(format_str, "ll", ft_strlen(format_str)))
		arg = va_arg(args, long long);
	else if (ft_strnstr(format_str, "l", ft_strlen(format_str)))
		arg = va_arg(args, long);
	else if (ft_strnstr(format_str, "hh", ft_strlen(format_str)))
		arg = va_arg(args, char);
	else if (ft_strnstr(format_str, "h", ft_strlen(format_str)))
		arg = va_arg(args, short);
	else
		arg = va_arg(args, int);
}