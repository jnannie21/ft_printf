/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnannie <jnannie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 05:36:27 by jnannie           #+#    #+#             */
/*   Updated: 2020/05/31 13:21:30 by jnannie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONVERSIONS "cspdiuxX%nfge"
# define INTEGER_CONVERSIONS "diuxX"
# define POINTER_CONVERSION "p"
# define FLOAT_CONVERSIONS "fge"
# define CHAR_CONVERSION "c"
# define STRING_CONVERSION "s"
# define COUNT_CONVERSION "n"
# define PERCENT_CONVERSION "%"
# define LENGTH_MODIFIERS "lh"

# include "libft/libft.h"
# include <stdarg.h>

int					ft_printf(const char *format, ...);
char				*ft_convert_integer(va_list args, char *format_str);

#endif
