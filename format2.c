/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:42:34 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 20:45:51 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*flag_alter_f(char *result, t_format *sf)
{
	char		*temp;

	if (!result)
		return (0);
	if (!sf->flagalter || sf->precision > 0)
		return (result);
	temp = ft_strjoin(result, ".");
	free(result);
	return (temp);
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
