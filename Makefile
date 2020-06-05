CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
MAIN_SOURCES = 	ft_printf.c ft_printf_utils.c conversions.c
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

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar cr $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $< -o $@

bonus:
	$(MAKE) DO_BONUS=1

$(LIBFT):
	$(MAKE) bonus -C libft/

clean:
	rm -f libft/*.o
	rm -f *.o

fclean: clean
	$(MAKE) fclean -C libft/
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re bonus libft
