/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 21:32:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 18:08:02 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	sf->ex10 = count_exp10(arg);
	if (sf->conversion == 'e')
		arg /= ft_pow10(sf->ex10);
	if (arg != 0)
		arg = round_float(arg, sf->precision);
	if (sf->conversion == 'e')
	{
		tmp_ex10 = count_exp10(arg);
		sf->ex10 += tmp_ex10;
		arg /= ft_pow10(tmp_ex10);
	}
	return (arg);
}

char			*addexp(char *result, int ex10)
{
	char		*strexp;

	strexp = ft_itoa(ex10);
	if (*strexp != '-')
		strexp = ft_strjoin_wrap(ft_strdup("+"), strexp);
	if (ex10 <= 9 && ex10 >= -9)
		strexp = fill_in(strexp, 1, ft_strlen(strexp) + 1, '0');
	result = ft_strjoin_wrap(result, ft_strdup("e"));
	result = ft_strjoin_wrap(result, strexp);
	return (result);
}

char			*remove_insignificant_zeros(char *result)
{
	char				*decimal_point;
	char				*temp1;
	char				*temp2;
	char				*last_zero;
	int					zeros;

	if (!(decimal_point = ft_strchr(result, '.')))
		return (result);
	last_zero = decimal_point + ft_strspn(decimal_point + 1, DEC_DIG);
	if (*last_zero != '0')
		return (result);
	zeros = 0;
	while (*(last_zero - zeros) == '0')
		zeros++;
	if (*(last_zero - zeros) == '.')
		zeros++;
	temp1 = ft_substr(result, 0, last_zero - zeros - result + 1);
	temp2 = result;
	result = ft_strjoin_wrap(temp1, ft_strdup(last_zero + 1));
	free(temp2);
	return (result);
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
