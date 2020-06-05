/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:06:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 12:14:10 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

size_t				print_output(t_list *output)
{
	while (output)
	{
		ft_putstr_fd(output->content, 1);
		output = output->next;
	}
}
