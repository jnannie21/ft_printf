/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 07:17:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/03 23:03:48 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MINUS_ZERO 0x8000000000000000
#define POSITIVE_INFINITY 0x7FF0000000000000
#define NEGATIVE_INFINITY 0xFFF0000000000000
#define MIN_PNAN 0x7FF0000000000001
#define MAX_PNAN 0x7FFFFFFFFFFFFFFF
#define MIN_NNAN 0xFFF0000000000001
#define MAX_NNAN 0xFFFFFFFFFFFFFFFF

static int				is_special_case(double d)
{
	if (d == 1.0 / 0.0 ||
		d == -1.0 / 0.0 ||
		d != d)
		return (1);
	return (0);
}

static char				*special_cases(long double d)
{
	if (d == 1.0 / 0.0)
		return (ft_strdup("inf"));
	else if (d == - 1.0 / 0.0)
		return (ft_strdup("-inf"));
	else if (d != d)
		return (ft_strdup("nan"));
	return (0);
	/*
	if (*((unsigned long *)&d) == POSITIVE_INFINITY)
		return (ft_strdup("inf"));
	else if (*((unsigned long *)&d) == NEGATIVE_INFINITY)
		return (ft_strdup("-inf"));
	else if (*((unsigned long *)&d) >= MIN_PNAN &&
			*((unsigned long *)&d) <= MAX_PNAN)
		return (ft_strdup("nan"));
	else if (*((unsigned long *)&d) >= MIN_NNAN &&
			*((unsigned long *)&d) <= MAX_NNAN)
		return (ft_strdup("-nan"));
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

static int				count_exp10(double d)
{
	int		pow;

	if (d == 0)
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

static char				*ftostr(double d, int prec, int len)
{
	int			digit;
	char		*temp;
	char		*result;
	double		ex10;
	double		rem;

	if (!(result = ft_calloc(len + (d < 0) + (prec > 0) + 1, sizeof(char))))
		return (0);
	temp = result;
	d = process_negative(d, &temp);
	d = d / ft_pow10(len - prec - 1);
	ex10 = 1;
	rem = 0;
	while (len--)
	{
		digit = d * ex10 - rem * 10;
		*temp++ = digit + '0';
		if (prec && len == prec)
			*temp++ = '.';
		rem = rem * 10 + digit;
		ex10 *= 10;
	}
	return (result);
}

char					*ft_ftoa(double d, int precision)
{
	int				sum_len;
	int				integer_len;

	if (is_special_case(d))
		return (special_cases(d));
	if ((integer_len = count_exp10(d) + 1) <= 0)
		integer_len = 1;
	sum_len = integer_len + precision;
	return (ftostr(d, precision, sum_len));
}
