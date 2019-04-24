NAME = wolf3d
FT_PRINTF = libftprintf.a
PATH_INC = ./src/fdf.h
LIBMLX_PATH = ./libmlx
CC = gcc
CFLAGS = -Wall -Wextra -Werror
BON_FL = -lm -lmlx -lXext -lX11 -L $(LIBMLX_PATH) -I $(LIBMLX_PATH)
HEAD = ./src/fdf.h

SRC =		./src/main.c\
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

$(NAME): $(FDF)
	cd ft_printf && make && cp libftprintf.a ../
	$(CC) -o $(NAME) $(SRC) $(BON_FL) libftprintf.a
clean:
	cd src && rm -f *.o
	cd ft_printf && make clean

fclean: clean
	cd ft_printf && make fclean
	/bin/rm -f $(NAME)
	/bin/rm -f libftprintf.a

re: fclean all