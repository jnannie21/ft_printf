/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 01:50:37 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/01 08:29:31 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strpbrk(const char *s, const char *accept)
{
	while (*s && (ft_strchr(accept, *s) == 0))
		s++;
	if (*s)
		return (s);
	return (0);
}
