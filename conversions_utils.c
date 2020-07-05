/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:09:07 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 22:17:46 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define UTF8_MAX_OCTETS 4

int				print_result(char *result, t_format *sf)
{
	int			len;

	len = -1;
	if (result)
		len = write(1, result, ft_strlen(result));
	free(result);
	sf->len += len;
	return (len);
}

char			*convert_c_length(t_format *sf)
{
	char		*result;
	wint_t		wc;

	wc = (wint_t)va_arg(sf->args, wint_t);
	if (sf->len_mod == 'l')
	{
		if ((result = ft_calloc(UTF8_MAX_OCTETS + 1, sizeof(char))))
			ft_wctomb(result, wc);
	}
	else
	{
		if ((result = ft_calloc(2, sizeof(char))))
			result[0] = (unsigned char)wc;
	}
	return (result);
}
