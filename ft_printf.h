/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/06/05 17:12:55 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define CONVERSIONS "cspdiuxX%nfge"
# define INTEGER_CONVERSIONS "diuxX"
# define POINTER_CONVERSION "p"
# define FLOAT_CONVERSIONS "fge"
# define CHAR_CONVERSION "c"
# define STRING_CONVERSION "s"
# define COUNT_CONVERSION "n"
# define PERCENT_CONVERSION "%"

int					ft_printf(const char *format, ...);
char				*ft_convert_di(va_list args, const char *format_str);
size_t				print_output(t_list *output);
char				*ft_convert_uxX(va_list args, const char *format);

#endif
