/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_float_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:32:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 23:35:49 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647

static double	round_float(double arg, int precision)
{
	double			del;

	del = 0.5;
	if (arg < 0)
		del = -0.5;
	del /= ft_pow10(precision);
	arg += del;
	return (arg);
}

double			prepare_arg(t_format *sf)
{
	int		tmp_ex10;
	double	arg;

	arg = sf->arg;
	sf->ex10 = ft_count_exp10(arg);
	if (sf->conversion == 'e')
		arg /= ft_pow10(sf->ex10);
	if (arg != 0)
		arg = round_float(arg, sf->precision);
	if (sf->conversion == 'e')
	{
		tmp_ex10 = ft_count_exp10(arg);
		sf->ex10 += tmp_ex10;
		arg /= ft_pow10(tmp_ex10);
	}
	return (arg);
}

int				is_exp_form(int ex10, int precision)
{
	if (ex10 < -4 || ex10 >= precision)
		return (1);
	return (0);
}

static void		precision_according_conversion(t_format *sf, int precision)
{
	prepare_arg(sf);
	if (is_exp_form(sf->ex10, precision))
	{
		sf->conversion = 'e';
		if (precision)
			sf->precision = precision - 1;
	}
	else
		sf->precision = precision - sf->ex10 - 1;
}

void			g_precision(t_format *sf)
{
	int			precision;

	if (sf->precision < 0)
		sf->precision = DEFAULT_PRECISION;
	if (!sf->precision)
		sf->precision++;
	precision = sf->precision;
	precision_according_conversion(sf, precision);
	precision_according_conversion(sf, precision);
}
