NAME = fdf
FT_PRINTF = libftprintf.a
PATH_INC = ./src/fdf.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
BON_FL = -lmlx -framework OpenGL -framework AppKit
HEAD = ./src/fdf.h

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
			./src/exit_x.c\

FDF_OBJ = $(FDF:.c=.o)

all: $(NAME)

$(NAME): $(FDF_OBJ) $(HEAD)
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) $(CFLAGS) $(BON_FL) -I -c $(FDF) libftprintf.a
	$(CC) -o $(NAME) $(FDF_OBJ) $(BON_FL) libftprintf.a
clean:
	cd src && rm -f *.o
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f libftprintf.a

re: fclean all