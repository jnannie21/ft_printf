/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 01:21:36 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/26 15:21:40 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define DEFAULT_PRECISION 6
#define MAXINT 2147483647

static char					*round_float(char *result)
{
	size_t			len;
	unsigned int	i;

	if (!ft_strchr(result, '.'))
		return (result);
	len = ft_strlen(result);
	i = 2;
	if (result[len - 1] >= '5')
	{
		i += result[len - i] == '.';
		while (i <= len && result[len - i] == '9')
		{
			result[len - i] = '0';
			i++;
			i += result[len - i] == '.';
		}
		if (i <= len && ft_isdigit(result[len - i]))
			result[len - i]++;
		else
			{
				if (i == len)
				{
					*result = '1';
					result = attach_prefix(result, "-");
				}
				else
					result = attach_prefix(result, "1");
				len++;
			}
	}
	result[len - 1] = '\0';
	return (result);
}

char						*ft_convert_f(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					precision;
	char				*precision_point;

	arg = (double)(va_arg(args, double));
	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		precision = ft_atoi(precision_point + 1);
	result = ft_ftoa(arg, (precision == MAXINT) ? MAXINT : precision + 1);
	if (precision < MAXINT)
		result = round_float(result);
	if (precision == 0)
		*(ft_strchr(result, '.')) = '\0';
	result = flag_plus_space(result, format);
	if (!is_special_case(arg))
		result = flag_numbersign_f(result, format);
	result = width(result, format);
	result = flag_minus(result, format);
	if (!is_special_case(arg))
		result = flag_zero(result, format);
	result = flag_space(result, format);
	return (result);
}

char						*ft_convert_e(va_list args, const char *format)
{
	char				*result;
	double				arg;
	int					precision;
	char				*precision_point;
	int					pow;
	char				*powstr;
	char				*temp;

	arg = (double)(va_arg(args, double));
	precision = DEFAULT_PRECISION;
	if ((precision_point = ft_strchr(format, '.')))
		precision = ft_atoi(precision_point + 1);
	pow = count_exp10(arg);
	powstr = ft_itoa(pow);
	result = ft_ftoa(arg / ft_pow10(pow), (precision == MAXINT) ? MAXINT : precision + 1);
	temp = result;
	result = ft_strjoin(result, powstr);
	free(powstr);
	free(temp);
}
