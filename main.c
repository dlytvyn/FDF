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
	gen->field[i] = 0xFFFFFF;
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

void     ft_scale(t_gen *gen)
{
	double scale;

	if (WINDOW_X - gen->max_x > WINDOW_Y - gen->max_y)
		scale = WINDOW_X / gen->max_x;
	else
		scale = WINDOW_Y / gen->max_y;
	scale = (scale / 100) * SCALE;
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x *= scale;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list->y *= scale;
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


void    print_in_window(t_gen *gen)
{
	int x_center;
	int y_center;
	int temp[2];
	t_fdf   *st;

	st = gen->run;
    gen->field = (int*)mlx_get_data_addr(gen->image, &gen->bits_per_pixel, &gen->size_line, &gen->endian);
	max_xy(gen);
	x_center = (WINDOW_X / 2) - (gen->max_x / 2);
	y_center = (WINDOW_Y / 2) - (gen->max_y / 2);
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x += x_center;
			gen->list->row = gen->list->row->next;
		}
		gen->list->y += y_center;
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
	st = st->next;
	while (gen->list)
    {
        while (gen->list->row->next)
        {
	        temp[0] = gen->list->row->x;
	        temp[1] = gen->list->y;
	        gen->list->row = gen->list->row->next;
	        line(temp[0], temp[1], gen->list->row->x, gen->list->y, gen);
//	        if (st->next)
//	        {
//		        line(temp[0], temp[1], st->row->x, st->y, gen);
//		        st->row = st->row->next;
//	        }
        }
	    gen->list->row = gen->list->clone;
        gen->list = gen->list->next;
	    if (st->next)
	        st = st->next;
    }
	gen->list = gen->run;
    mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
    mlx_destroy_image(gen->init, gen->image);
    mlx_loop(gen->init);
}

int main(int argc, char **argv)
{
	t_gen   gen;
	int     fd;

    argc = 1;
    gen.list = new_list();
	gen.run = gen.list;
    argv[1] = "dd";
    //open(argv[1], O_RDONLY);
	fd = open("/Users/dlytvyn/FDF/test_maps/42.fdf", O_RDONLY);
    reader(&gen, fd);
	ft_scale(&gen);
    gen.init = mlx_init();
	gen.window = mlx_new_window(gen.init, WINDOW_X, WINDOW_Y, "FDF Project!");
	gen.image = mlx_new_image(gen.init, WINDOW_X, WINDOW_Y);
    print_in_window(&gen);
}
