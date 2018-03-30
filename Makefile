NAME = fdf
LIBFT = ./libft/libft.a
FT_PRINTF = ./ft_printf/libftprintf.a
GNL = ./GNL/get_next_line.c
CC = gcc

CFLAGS = -Wall -Wextra -Werror -Iincludes -lmlx -framework OpenGL -framework AppKit

FDF =		./src/main.c\
			./src/bresenham.c\
			./src/centering.c\
			./src/change_coordinates.c\
			./src/check_colors.c\
			./src/ft_atoi_base.c\
			./src/is_valid.c\
			./src/manage_keys.c\
			./src/max_xy.c\
			./src/movement.c\
			./src/mp_rotation.c\
			./src/print_in_window.c\
			./src/reader.c\
			./src/scale.c\

FDF_OBJ = $(FDF:.c=.o)

all: $(NAME)

$(NAME):
	cd libft && make && cp libft.a ../
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) $(CFLAGS) $(FDF) $(LIBFT) $(FT_PRINTF) $(GNL) -o $(NAME)
clean:
	cd src && rm -f $(FILLER_OBJ)
	cd libft && make clean
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	cd libft && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f colors
	/bin/rm -f libftprintf.a
	/bin/rm -f libft.a

re: fclean all