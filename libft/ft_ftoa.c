/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 07:17:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/26 15:42:12 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MINUS_ZERO 0x8000000000000000
#define POSITIVE_INFINITY 0x7FF0000000000000
#define NEGATIVE_INFINITY 0xFFF0000000000000
#define MIN_NAN 0x7FF0000000000001
#define MAX_NAN 0x7FFFFFFFFFFFFFFF

static char				*special_cases(double d)
{
	if (*((unsigned long *)&d) == POSITIVE_INFINITY)
		return (ft_strdup("inf"));
	else if (*((unsigned long *)&d) == NEGATIVE_INFINITY)
		return (ft_strdup("-inf"));
	else if (*((unsigned long *)&d) >= MIN_NAN &&
			*((unsigned long *)&d) <= MAX_NAN)
		return (ft_strdup("nan"));
	return (0);
/*
	if (d == 1.0 / 0.0)
		return (ft_strdup("inf"));
	else if (d == -1.0 / 0.0)
		return (ft_strdup("-inf"));
	else if (d != d)
		return (ft_strdup("nan"));
	return (0);
*/
}

static double			process_negative(double d, char **temp)
{
	if (d < 0 || *((unsigned long *)&d) == MINUS_ZERO)
	{
		**temp = '-';
		(*temp)++;
		d *= (-1);
	}
	return (d);
}

char					*ft_ftoa(double d, int precision)
{
	char			*result;
	char			*temp;
	int				digit;
	int				len;
	int				integers;

	if ((result = special_cases(d)))
		return (result);
	if ((integers = count_exp10(d) + 1) <= 0)
		integers = 1;
	len = integers + precision;
	result = ft_calloc(len + (d < 0) + (precision > 0) + 1, sizeof(char));
	temp = result;
	d = process_negative(d, &temp);
	d = d / ft_pow10(len - precision);
	while (len--)
	{
		d *= 10;
		digit = d;
		*temp++ = digit + '0';
		if (precision && len == precision)
			*temp++ = '.';
		d -= digit;
	}
	return (result);
}
