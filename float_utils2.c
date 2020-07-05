/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversions_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:36:42 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 20:37:33 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						count_exp10(double d)
{
	int		pow;

	if (is_special_case(d) || d == 0)
		return (0);
	if (d < 0)
		d *= (-1);
	pow = 0 - (d < 1);
	if (d >= 1)
		while ((d /= 10) >= 1)
			pow++;
	else
		while ((d *= 10) < 1)
			pow--;
	return (pow);
}

int						is_special_case(double d)
{
	if (*((unsigned long *)&d) == POSITIVE_INFINITY ||
		*((unsigned long *)&d) == NEGATIVE_INFINITY ||
		(*((unsigned long *)&d) >= MIN_PNAN &&
		*((unsigned long *)&d) <= MAX_PNAN) ||
		(*((unsigned long *)&d) >= MIN_NNAN &&
		*((unsigned long *)&d) <= MAX_NNAN))
		return (1);
	return (0);
}