#include "fdf.h"

// gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit main.c GNL/get_next_line.c libft.a

void    clear(t_gen *gen)
{
	ft_bzero(gen->field, WINDOW_X * WINDOW_Y * 4);
	gen->size_line = 0;
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}

void put_pixel(int x, int y, t_gen *gen)
{
	int i;

	if (x >= gen->size_line / 4 || x < 0 || y < 0)
		return ;
	i = (x + (y * (gen->size_line / 4)));
	gen->field[i] = 0xFFFFFF;
}

static int            ft_incline(t_fdf t1, t_fdf t2)
{
    return (fabs(t2.y - t1.y) > fabs(t2.x - t1.x));
}

static void            ft_swap(t_fdf *t1, t_fdf *t2, int i)
{
    double    tmp;

    if (i == 1)
    {
        tmp = t1->x;
        t1->x = t1->y;
        t1->y = tmp;
        tmp = t2->x;
        t2->x = t2->y;
        t2->y = tmp;
    }
    else
    {
        tmp = t1->x;
        t1->x = t2->x;
        t2->x = tmp;
        tmp = t1->y;
        t1->y = t2->y;
        t2->y = tmp;
        tmp = (double)t1->color;
        t1->color = t2->color;
        t2->color = (int)tmp;
    }
}

void                line(t_gen *gen, t_fdf t1, t_fdf t2)
{
    double dx;
    double dy;
    double steep;
    double err;
    double ystep;

    if ((steep = ft_incline(t1, t2)))
        ft_swap(&t1, &t2, 1);
    if (t1.x > t2.x)
        ft_swap(&t1, &t2, 0);
    dx = t2.x - t1.x;
    dy = fabs(t2.y - t1.y);
    err = dx / 2;
    ystep = (t1.y < t2.y) ? 1 : -1;
    while (t1.x++ < t2.x)
    {
        put_pixel(steep ? t1.y : t1.x, steep ? t1.x : t1.y, gen);
        err -= dy;
        if (err < 0)
        {
            t1.y += ystep;
            err += dx;
        }
    }
}

 void    max_xy(t_gen *gen)
 {
	 int i;
	 int j;

	 i = 0;
	 gen->min_x = gen->list[0][0].x;
	 gen->min_y = gen->list[0][0].y;
	 while (i < gen->w_h)
	 {
		 j = 0;
		 while (j < gen->w_w)
		 {
			 if (gen->list[i][j].x > gen->max_x)
				 gen->max_x = gen->list[i][j].x;
			 if (gen->list[i][j].y > gen->max_y)
				 gen->max_y = gen->list[i][j].y;
			 if (gen->list[i][j].x < gen->min_x)
				 gen->min_x = gen->list[i][j].x;
			 if (gen->list[i][j].y < gen->min_y)
				 gen->min_y = gen->list[i][j].y;
			 j++;
		 }
		 i++;
	 }
 }

 void     ft_scale(t_gen *gen)
 {
	 int i;
	 int j;

	 i = 0;
	 while (i < gen->w_h)
	 {
		 j = 0;
		 while (j < gen->w_w)
		 {
			 gen->list[i][j].x *= gen->scale;
			 gen->list[i][j].y *= gen->scale;
			 gen->list[i][j].z *= gen->scale;
			 j++;
		 }
		 i++;
	 }
 }

 void	get_scale(t_gen *gen)
 {
 	if (WINDOW_X - gen->max_x > WINDOW_Y - gen->max_y)
 		gen->scale = WINDOW_X / gen->max_x;
 	else
 		gen->scale = WINDOW_Y / gen->max_y;
 	gen->scale = (gen->scale / 100) * SCALE;
 	ft_scale(gen);
 }

int		array_len(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
		i++;
	return (i);
}

void	separate_data(t_gen *gen)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	array = ft_strsplit(gen->buf, ' ');
	gen->list = (t_fdf**)malloc(sizeof(t_fdf*) * gen->w_h);
	i = 0;
	k = 0;
	while (i < gen->w_h)
	{
		j = 0;
		gen->list[i] = (t_fdf*)malloc(sizeof(t_fdf) * gen->w_w);
		while (j < gen->w_w)
		{
			gen->list[i][j].x = j;
			gen->list[i][j].y = i;
			gen->list[i][j].z = ft_atoi(array[k]);
			k++;
			j++;
		}
		i++;
	}
	gen->max_x = gen->w_w - 1;
	gen->max_y = gen->w_h - 1;

}

void   reader(t_gen *gen, int fd)
{
	char    *line;
	char    **array;

	get_next_line(fd, &line);
	gen->buf = ft_strdup(line);
	array = ft_strsplit(line, ' ');
	ft_strdel(&line);
	gen->w_w = array_len(array);
	gen->w_h = 1;
	while (get_next_line(fd, &line))
	{
		gen->buf = ft_strjoin(gen->buf, " ");
		gen->buf = ft_strjoin(gen->buf, line);
		ft_strdel(&line);
		gen->w_h++;
	}
	separate_data(gen);
}

int exit_x(void)
{
	exit(0);
}

void    print_in_window(t_gen *gen)
{
	int	i;
	int	j;

    gen->field = (int*)mlx_get_data_addr(gen->image, &gen->bits_per_pixel, &gen->size_line, &gen->endian);
	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			if (i + 1 < gen->w_h)
				line(gen, gen->list[i][j], gen->list[i + 1][j]);
			if (j + 1 < gen->w_w)
				line(gen, gen->list[i][j], gen->list[i][j + 1]);
			j++;
		}
		i++;
	}
    mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}

// void    centering_zoom(t_gen *gen)
// {
// 	double x_center;
// 	double y_center;
// 	int		i;
// 	int		j;

// 	max_xy(gen);
// 	i = 0;
// 	while (i < gen->w_h)
// 	{
// 		j = 0;
// 		while (j < gen->w_w)
// 		{
// 			gen->list[i][j].x += x_center;
// 			gen->list[i][j].y += y_center;
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	centering(t_gen *gen)
{
	int	x;
	int	y;
	int i;
	int j;

	max_xy(gen);
	x = (WINDOW_X / 2) - ((gen->max_x + gen->min_x) / 2);
	y = (WINDOW_Y / 2) - ((gen->max_y + gen->min_y) / 2);
	i = 0;
	while (i < gen->w_h)
	 {
		 j = 0;
		 while (j < gen->w_w)
		 {
			 gen->list[i][j].x += x;
			 gen->list[i][j].y += y;
			 j++;
		 }
		 i++;
	 }
}

int	manage_keys(int key, t_gen *gen)
{
	if (key == 53)
		exit_x();
	else if (key == 6)
		gen->deg_z = 1 * M_PI / 180;
	else if (key == 0)
		gen->deg_z = -1 * M_PI / 180;
	else if (key == 7)
		gen->deg_x = 1 * M_PI / 180;
	else if (key == 8)
		gen->deg_x = -1 * M_PI / 180;
	else if (key == 16)
		gen->deg_y = 1 * M_PI / 180;
	else if (key == 17)
		gen->deg_y = -1 * M_PI / 180;
	else if (key == 116)
		increase(gen, 10);
	else if (key == 121)
		increase(gen, -10);
	else if (key == 123)  //to left
		move_to_left(gen);
	else if (key == 124)  // to right
		move_to_right(gen);
	else if (key == 126)   // move up
		move_up(gen);
	else if (key == 125) // move down
		move_down(gen);
	else if (key == 69)
	{
		gen->scale = 1.1;
		minus_coor(gen);
		ft_scale(gen);
		plus_coor(gen);
	}
	else if (key == 78)
	{
		gen->scale = 0.9;
		minus_coor(gen);
		ft_scale(gen);
		plus_coor(gen);
	}
	rotate_matrix(gen, key);
	//mlx_clear_window(gen->init, gen->window);
	clear(gen);
	print_in_window(gen);
	return (0);
}

void	inicialization(t_gen *gen)
{
	gen->max_x = 0;
	gen->max_y = 0;
	gen->bits_per_pixel = 0;
	gen->diff_x = 0;
	gen->diff_y = 0;
	gen->endian = 0;
	gen->image = 0;
	gen->init = 0;
	gen->max_x = 0;
	gen->min_x = 0;
	gen->max_y = 0;
	gen->min_y = 0;
	gen->scale = 0;
	gen->size_line = 0;
	gen->w_h = 0;
	gen->w_w = 0;
	gen->window = 0;
	gen->deg_x = 0;
	gen->deg_y = 0;
	gen->deg_z = 0;
}

int main(int argc, char **argv) {
	t_gen gen;
	int fd;

	argc = 1;
	argv[1] = "dd";
	inicialization(&gen);
	//open(argv[1], O_RDONLY);
	fd = open("/Users/dlytvyn/FDF/test_maps/42.fdf", O_RDONLY);
	reader(&gen, fd);
	get_scale(&gen);
	gen.init = mlx_init();
	gen.window = mlx_new_window(gen.init, WINDOW_X, WINDOW_Y, "FDF Project!");
	gen.image = mlx_new_image(gen.init, WINDOW_X, WINDOW_Y);
	centering(&gen);
	print_in_window(&gen);
	mlx_hook(gen.window, 2, 5, manage_keys, &gen);
	mlx_hook(gen.window, 17, 1L << 17, exit_x, &gen);
	mlx_loop(gen.init);
}