/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/09 19:00:15 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int					ft_printf(const char *format, ...);
char				*ft_convert_di(va_list args, const char *format_str);
char				*ft_convert_u(va_list args, const char *format);
char				*ft_convert_xX(va_list args, const char *format);
char				*ft_convert_c(va_list args, const char *format);
char				*ft_convert_s(va_list args, const char *format);
char				*ft_convert_prcnt(va_list args, const char *format);
char				*ft_convert_ptr(va_list args, const char *format);
size_t				ft_printf_count_len(int set_zero, size_t l);
char				*ft_convert_n(va_list args, const char *format);

#endif
