/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 03:09:07 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/15 03:31:04 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

size_t						output_len(int increase, size_t l)
{
	static size_t		len;
	size_t				temp;

	temp = len;
	if (increase)
		len += l;
	else
		len = l;
	return (temp);
}
