/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:06:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 13:14:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

size_t				print_output(t_list *output)
{
	size_t		len;

	len = 0;
	while (output)
	{
		ft_putstr_fd(output->content, 1);
		len = len +ft_strlen(output->content);
		output = output->next;
	}
	return (len);
}
