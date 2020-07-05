/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 01:53:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/04 20:26:45 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define FLAGS "-0# +"
#define LENGTH_MODIFIERS "lh"
#define CONVERSIONS "cspdiuxX%nfge"

static void				parse_flags(t_format *sf)
{
	size_t		flags_len;

	flags_len = ft_strspn(sf->format, FLAGS);
	if (ft_memchr(sf->format, '#', flags_len))
		sf->flagalter = 1;
	if (ft_memchr(sf->format, '+', flags_len))
		sf->flagplus = 1;
	else if (ft_memchr(sf->format, ' ', flags_len))
		sf->flagspace = 1;
	if (ft_memchr(sf->format, '-', flags_len))
		sf->flagminus = 1;
	else if (ft_memchr(sf->format, '0', flags_len))
		sf->flagzero = 1;
	sf->format += flags_len;
}

static void				parse_width(t_format *sf)
{
	if (*sf->format == '*')
	{
		sf->width = (int)(va_arg(sf->args, int));
		if (sf->width < 0)
		{
			sf->width *= (-1);
			sf->flagminus = 1;
		}
		sf->format++;
	}
	else
	{
		sf->width = ft_atoi(sf->format);
		sf->format += ft_strspn(sf->format, DEC_DIG);
	}
}

static void				parse_precision(t_format *sf)
{
	if (*sf->format != '.')
		return ;
	sf->format++;
	if (*sf->format == '*')
	{
		sf->precision = (int)(va_arg(sf->args, int));
		sf->format++;
	}
	else
	{
		sf->precision = ft_atoi(sf->format);
		sf->format += ft_strspn(sf->format, DEC_DIG);
	}
}

static void				parse_length(t_format *sf)
{
	if (!ft_strchr(LENGTH_MODIFIERS, *sf->format))
		return ;
	sf->len_mod = *sf->format;
	sf->format++;
	if ((*sf->format == sf->len_mod) &&
		(*sf->format == 'h' || *sf->format == 'l'))
		{
			sf->len_mod *= 2;
			sf->format++;
		}
}

static void				parse_conversion(t_format *tf)
{
	if (!ft_strchr(CONVERSIONS, *tf->format) || *tf->format == '\0')
		return ;
	tf->conversion = *tf->format;
	tf->format++;
}

void					parse_format(t_format *sf)
{
	if (*sf->format != '%')
		return ;
	sf->format++;
	parse_flags(sf);
	parse_width(sf);
	parse_precision(sf);
	parse_length(sf);
	parse_conversion(sf);
}
