CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
MAIN_SOURCES = 	ft_printf.c f_conversions.c i_conversions.c other_conversions.c 	\
				utils1.c utils2.c float_utils1.c float_utils2.c						\
				format1.c format2.c format3.c parse_format.c						\
				ft_ftoa.c
BONUS_SOURCES =
HEADER = ft_printf.h
NAME = libftprintf.a
LIBFT = libft/libft.a
DO_BONUS = 0

ifeq ($(DO_BONUS), 1)
	OBJECTS = $(MAIN_SOURCES:.c=.o) $(BONUS_SOURCES:.c=.o)
else
	OBJECTS = $(MAIN_SOURCES:.c=.o)
endif

all: makelibft $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar cr $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c $(HEADER)
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
