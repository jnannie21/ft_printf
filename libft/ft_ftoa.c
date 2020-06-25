/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 07:17:58 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/25 15:08:49 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//#define MAX_DOUBLE_LENGTH 310

static unsigned int		integer_len(double d)
{
	unsigned int	len;

	len = 1;
	if (d < 0)
		d *= (-1);
	while ((d /= 10) > 1)
		len++;
	return (len);
}

static double			ft_pow10(unsigned int n)
{
	double			res;

	res = 1;
	while (n--)
		res *= 10;
	return (res);
}

static char				*special_cases(double d)
{
	if (d == 1.0 / 0.0)
		return (ft_strdup("inf"));
	else if (d == -1.0 / 0.0)
		return (ft_strdup("-inf"));
	else if (d != d)
		return (ft_strdup("nan"));
	return (0);
}

static double			process_negative(double d, char **temp)
{
	if (d < 0 || d == -0.0)
	{
		**temp = '-';
		(*temp)++;
		d *= (-1);
	}
	return (d);
}

char					*ft_ftoa(double d, unsigned int precision)
{
	char			*result;
	char			*temp;
	double			pow;
	int				digit;
	int				len;

	if ((result = special_cases(d)))
		return (result);
	len = integer_len(d) + precision;
	result = ft_calloc(len + (d < 0) + (precision > 0) + 1, sizeof(char));
	temp = result;
	d = process_negative(d, &temp);
	pow = ft_pow10(len - precision - 1);
	while (len--)
	{
		digit = d / pow;
		*temp++ = digit + '0';
		if (pow == 1 && precision)
			*temp++ = '.';
		d = d - pow * digit;
		pow /= 10;
	}
	return (result);
}
