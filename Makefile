CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
MAIN_SOURCES = 	ft_printf.c f_conversions.c i_conversions.c other_conversions.c 	\
				conversions_utils.c float_utils.c									\
				format1.c format2.c format3.c parse_format.c
BONUS_SOURCES = bonus_ft_printf.c bonus_f_conversions.c bonus_i_conversions.c		\
				bonus_other_conversions.c bonus_conversions_utils.c					\
				bonus_float_utils.c bonus_format1.c bonus_format2.c					\
				bonus_format3.c bonus_parse_format.c
NAME = libftprintf.a
LIBFT = libft/libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(BONUS_SOURCES:.c=.o)
	HEADER = bonus_ft_printf.h
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
	HEADER = ft_printf.h
endif

all: makelibft $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(HEADER)
	cp $(LIBFT) $(NAME)
	ar cr $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

makelibft:
	$(MAKE) bonus -C libft/

clean:
	rm -f libft/*.o
	rm -f *.o

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus makelibft
