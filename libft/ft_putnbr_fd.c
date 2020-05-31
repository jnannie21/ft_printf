/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 14:52:39 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/10 15:29:47 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		ft_pow10(int n)
{
	long		res;

	res = 1;
	while (n--)
		res *= 10;
	return (res);
}

static int		count_num(int n)
{
	int		num;

	num = 1;
	while (n / ft_pow10(num) != 0)
		num++;
	return (num);
}

void			ft_putnbr_fd(int n, int fd)
{
	int		num;

	num = count_num(n);
	if (n >= 0)
		n *= (-1);
	else
		ft_putchar_fd('-', fd);
	while (num--)
		ft_putchar_fd((-1) * ((n / ft_pow10(num)) % 10 - 48), fd);
}
