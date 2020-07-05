/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 18:23:18 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int				print_regular_text(t_format *sf)
{
	int			len;
	char		*prcnt;

	prcnt = ft_strchrnul(sf->format, '%');
	len = write(1, sf->format, prcnt - sf->format);
	sf->format += len;
	sf->len += len;
	return (len);
}

static int					convert(t_format *sf)
{
	if (sf->conversion == '\0')
		return (print_regular_text(sf));
	else if (sf->conversion == 'd' || sf->conversion == 'i')
		return (ft_convert_di(sf));
	else if (sf->conversion == 'u')
		return (ft_convert_u(sf));
	else if (sf->conversion == 'x' || sf->conversion == 'X')
		return (ft_convert_xX(sf));
	else if (sf->conversion == 'c')
		return (ft_convert_c(sf));
	else if (sf->conversion == 's')
		return (ft_convert_s(sf));
	else if (sf->conversion == '%')
		return (ft_convert_prcnt(sf));
	else if (sf->conversion == 'p')
		return (ft_convert_ptr(sf));
	else if (sf->conversion == 'n')
		return (ft_convert_n(sf));
	else if (sf->conversion == 'f')
		return (ft_convert_f(sf));
	else if (sf->conversion == 'e')
		return (ft_convert_e(sf));
	else if (sf->conversion == 'g')
		return (ft_convert_g(sf));
	return (-1);
}

static void				init_sf(t_format *sf)
{
	sf->arg = 0;
	sf->ex10 = 0;
	sf->width = 0;
	sf->precision = -1;
	sf->flagalter = 0;
	sf->flagplus = 0;
	sf->flagminus = 0;
	sf->flagzero = 0;
	sf->flagspace = 0;
	sf->len_mod = 0;
	sf->conversion = '\0';
}

int						ft_printf(const char *format, ...)
{
	t_format	*sf;
	size_t		len;

	if (!(sf = malloc(sizeof(t_format))))
		return (-1);
	va_start(sf->args, format);
	sf->len = 0;
	sf->format = (char *)format;
	while (*(sf->format))
	{
		init_sf(sf);
		parse_format(sf);
		if (convert(sf) == -1)
			break ;
	}
	va_end(sf->args);
	len = sf->len;
	if (*(sf->format) != '\0')
		len = -1;
	free(sf);
	return (len);
}
