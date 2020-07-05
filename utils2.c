/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 20:35:31 by jnannie           #+#    #+#             */
/*   Updated: 2020/07/05 20:36:58 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char						*ft_strjoin_wrap(char *str1, char *str2)
{
	char	*result;

	result = 0;
	if (str1 && str2)	
		result = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (result);
}
