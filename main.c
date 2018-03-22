/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:39:42 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/16 12:39:43 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit main.c GNL/get_next_line.c libft.a


// set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lmlx -framework OpenGL -framework AppKit")

t_row   *new_row_list()
{
	t_row   *list;

	list = (t_row*)malloc(sizeof(t_row));
	list->x = 0;
	list->z = 0;
	list->color = NULL;
	list->next = NULL;
	return (list);
}

t_fdf   *new_list()
{
	t_fdf   *list;

	list = (t_fdf*)malloc(sizeof(t_fdf));
	list->row = new_row_list();
	list->clone = list->row;
	list->y = 0;
	list->next = NULL;
	return (list);
}

void   reader(t_gen *gen, int fd)
{
	char    *line;
	char    **array;
	int     i;
	int     j;

	j = 0;
	while (get_next_line(fd, &line))
	{
		array = ft_strsplit(line, ' ');
		i = 0;
		if (j > 0)
		{
			gen->list->next = new_list();
			gen->list = gen->list->next;
		}
		while (array[i])
		{
			if (i > 0)
			{
				gen->list->row->next = new_row_list();
				gen->list->row = gen->list->row->next;
			}
			gen->list->row->x = i;
			gen->list->y = j;
			gen->list->row->z = ft_atoi(array[i]);
			if (i > gen->max_x)
				gen->max_x = i;
			i++;
		}
		gen->list->row = gen->list->clone;
		if (j > gen->max_y)
			gen->max_y = j;
		ft_strdel(&line);
		j++;
	}
	gen->list = gen->run;
}

void put_pixel(int x, int y, t_gen *gen)
{
	int i;
	i = (x + (y * (gen->size_line / 4)));
//	printf("iiii: %d\n", i);
	gen->field[i] = 0xFFFFFF;
//	printf("ggggggg\n");
}

//void    line(int xy[2], int x1, int y1, t_gen *gen)
//{
//    int dx[2];
//    int sx;
//    int sy;
//    int err;
//    int e2;
//
//    dx[0] = abs(x1 - xy[0]);
//    dx[1] = abs(y1 - xy[1]);
//    sx = xy[0] < x1 ? 1 : -1;
//    sy = xy[1] < y1 ? 1 : -1;
//    err = (dx[0] > dx[1] ? dx[0] : -dx[1]) / 2;
//    while (1)
//    {
//        put_pixel(xy[0], xy[1], gen);
//        if (xy[0] == x1 && xy[1] == y1)
//            break;
//        e2 = err;
//        if (e2 > -dx[0])
//            err -= dx[1]; xy[0] += sx;
//        if (e2 < dx[1])
//            err += dx[0]; xy[1]+= sy;
//    }
//}

void line(int x0, int y0, int x1, int y1, t_gen *gen) {

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		put_pixel(x0,y0, gen);
		if (x0==x1 && y0==y1) break;
		e2 = err;
		if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
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

void     ft_scale(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x *= gen->scale;
			gen->list->row->z *= gen->scale;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list->y *= gen->scale;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    max_xy(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			if (gen->list->row->x > gen->max_x)
				gen->max_x = gen->list->row->x;
			gen->list->row = gen->list->row->next;
		}
		if (gen->list->y > gen->max_y)
			gen->max_y = gen->list->y;
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

int exit_x(void)
{
	exit(0);
}

void    clear(t_gen *gen)
{
	ft_bzero(gen->field, WINDOW_X * WINDOW_Y * 4);
	gen->size_line = 0;
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}

int	manage_keys(int key, t_gen *gen)
{
	if (key == 6)
		gen->angle_z += 2;
	else if (key == 7)
		gen->angle_x += 2;
	else if (key == 16)
		gen->angle_y += 2;
	else if (key == 53)
		exit_x();
	else if (key == 123)  //to left
		move_to_left(gen);
	else if (key == 124)  // to right
		move_to_right(gen);
	else if (key == 126)   // move up
		move_up(gen);
	else if (key == 125) // move down
		move_down(gen);
	else if (key == 116)
		increase(gen);
	else if (key == 121)
		decrease(gen);
	else if (key == 69)
	{
		gen->scale = 1.1;
		ft_scale(gen);
		centering(gen);
	}
	else if (key == 78)
	{
		gen->scale = 0.9;
		ft_scale(gen);
		centering(gen);
	}
	//printf("Angle x: %d\n", gen->angle_x);
	rotate_matrix(gen, key);
	//mlx_destroy_image(gen->init, gen->image);
	mlx_clear_window(gen->init, gen->window);
	clear(gen);
	print_in_window(gen);
	return (0);
}

void    centering(t_gen *gen)
{
	int x_center;
	int y_center;

	max_xy(gen);
	x_center = (WINDOW_X / 2) - (gen->max_x / 2);
	y_center = (WINDOW_Y / 2) - (gen->max_y / 2);
	while (gen->list)
	{
		while (gen->list->row)
		{
			//printf("X before: %f\n", gen->list->row->x);
			gen->list->row->x += x_center;
			//printf("X_center: %d\n", x_center);
			//printf("Y_center: %d\n", y_center);
			//printf("X after centering: %f\n", gen->list->row->x);
			gen->list->row = gen->list->row->next;
		}
		gen->list->y += y_center;
		printf("Y after centering: %f\n", gen->list->y);
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
	printf("Exit\n");
}

void    print_in_window(t_gen *gen)
{
	int temp[2];

	gen->field = (int*)mlx_get_data_addr(gen->image, &gen->bits_per_pixel, &gen->size_line, &gen->endian);
	while (gen->list)
	{
		while (gen->list->row)
		{
			temp[0] = gen->list->row->x;
			temp[1] = gen->list->y;
			if (gen->list->row->next)
				line(temp[0], temp[1], gen->list->row->next->x, gen->list->y, gen);    // horizontal lines
			else if (gen->list->next)
				line(gen->list->row->x, gen->list->y, gen->list->row->x, gen->list->next->y, gen); // last vertical line
			if (gen->list->next)
				line(temp[0], temp[1], gen->list->row->x, gen->list->next->y, gen);   // vertical lines
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
		printf("here\n");
	}
	//printf("here it is\n");
	gen->list = gen->run;
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
	//mlx_destroy_image(gen->init, gen->image);
	//printf("come\n");
}

int main(int argc, char **argv) {
	t_gen gen;
	int fd;

	argc = 1;
	gen.max_x = 0;
	gen.max_y = 0;
	gen.angle_x = 0;
	gen.angle_y = 0;
	gen.angle_z = 0;
	gen.list = new_list();
	gen.run = gen.list;
	argv[1] = "dd";
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