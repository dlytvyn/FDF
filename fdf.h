#include <stdio.h>
#include <math.h>
#include "/Users/dlytvyn/FDF/New_try/minilibx/mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include </Users/dlytvyn/FDF/New_try/GNL/get_next_line.h>

# define WINDOW_X 1500
# define WINDOW_Y 1000
# define SCALE    60

typedef struct      s_fdf
{
    double         	x;
    double         	z;
    double          y;
    int             color;
}                   t_fdf;

typedef struct      s_gen
{
	struct  s_fdf   **list;
	int             *field;
	char			*buf;
	int             bits_per_pixel;
	int             size_line;
	int             endian;
	int				w_h;
	int				w_w;
	int             max_x;
	int             max_y;
	int				min_x;
	int				min_y;
	void            *init;
	void            *window;
	void            *image;
	double			scale;
	double			diff_x;
	double			diff_y;
	double			deg_x;
	double			deg_y;
	double			deg_z;
}                   t_gen;

void    rotate_matrix(t_gen *gen, int key);
void    print_in_window(t_gen *gen);
void    move_to_left(t_gen *gen);
void    move_to_right(t_gen *gen);
void    move_up(t_gen *gen);
void    move_down(t_gen *gen);
void    centering(t_gen *gen);
void    ft_scale(t_gen *gen);
void    max_xy(t_gen *gen);
void    rotate_matrix(t_gen *gen, int key);
void	increase(t_gen *gen,int a);
void	plus_coor(t_gen *gen);
void	minus_coor(t_gen *gen);
//void    centering_zoom(t_gen *gen);
