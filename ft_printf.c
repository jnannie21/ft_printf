/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:31:18 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/02 16:42:17 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define PRINTABLE 127

typedef int (*conversion_func)(t_format *);

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

static conversion_func		*get_conversions(void)
{
	static conversion_func	conversions[PRINTABLE];

	if (!conversions['\0'])
	{
		conversions['\0'] = print_regular_text;
		conversions['d'] = ft_convert_di;
		conversions['i'] = ft_convert_di;
		conversions['u'] = ft_convert_u;
		conversions['x'] = ft_convert_xX;
		conversions['X'] = ft_convert_xX;
		conversions['c'] = ft_convert_c;
		conversions['s'] = ft_convert_s;
		conversions['%'] = ft_convert_prcnt;
		conversions['p'] = ft_convert_ptr;
		conversions['n'] = ft_convert_n;
		conversions['f'] = ft_convert_f;
		conversions['e'] = ft_convert_e;
		conversions['g'] = ft_convert_g;
	}
	return (conversions);
}

static int					process_format(t_format *sf)
{
	if (!sf->conversion)
	{
		if (print_regular_text(sf) == -1)
			return (0);
		return (1);
	}
	return (get_conversions()[(int)sf->conversion](sf));
}

static void				init_sf(t_format *form)
{
	form->width = 0;
	form->precision = -1;
	form->flagalter = 0;
	form->flagplus = 0;
	form->flagminus = 0;
	form->flagzero = 0;
	form->flagspace = 0;
	form->len_mod = 0;
	form->conversion = '\0';
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
		if (process_format(sf) == -1)
			break ;
	}
	va_end(sf->args);
	len = sf->len;
	if (*(sf->format) != '\0')
		len = -1;
	free(sf);
	return (len);
}
