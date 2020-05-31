/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 01:50:37 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/31 02:18:13 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				ft_strcspn(const char *s, const char *reject)
{
	size_t		i;

	i = 0;
	while (s[i] && (ft_strchr(reject, s[i]) == 0))
		i++;
	return (i);
}
