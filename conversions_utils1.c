/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:09:07 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/04 20:24:11 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						print_result(char *result, t_format *sf)
{
	int					len;

	len = -1;
	if (result)
		len = write(1, result, ft_strlen(result));
	free(result);
	sf->len += len;
	return (len);
}

char					*u_itoa_base(unsigned long long n, int base)
{
	char				*last_digit;
	char				*result;
	char				*remains;

	last_digit = ft_itoa_base(n % base, base);
	if (n / base != 0)
		remains = ft_itoa_base(n / base, base);
	else
		remains = ft_strdup("");
	result = 0;
	if (last_digit && remains)
		result = ft_strjoin(remains, last_digit);
	free(remains);
	free(last_digit);
	return (result);
}

char					*strtolower(char *str)
{
	unsigned int		i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
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

static void				strcpytoend(char *dest, const char *src)
{
	size_t		dest_len;
	size_t		src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	ft_memcpy(dest + dest_len - src_len, src, src_len);
}

char					*fill_in(char *result, int pos,
								unsigned int length, char filler)
{
	char	*temp;

	if (length <= ft_strlen(result))
		return (result);
	temp = result;
	if (!(result = ft_calloc(length + 1, sizeof(char))))
		return (0);
	ft_memset(result, filler, length);
	strcpytoend(result, temp + pos);
	ft_memcpy(result, temp, pos);
	free(temp);
	return (result);
}
