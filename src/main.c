/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:12:04 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:12:05 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			clear(t_gen *gen)
{
	ft_bzero(gen->field, WINDOW_X * WINDOW_Y * 4);
	gen->size_line = 0;
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}

void			inicialization(t_gen *gen)
{
    gen->buf = ft_strdup("");
		gen->bits_per_pixel = 0;
	gen->endian = 0;
	gen->image = 0;
	gen->init = 0;
    gen->pos_x = 22;
    gen->pos_y = 12;
    gen->dir_x = -1;
    gen->dir_y = 0;
    gen->plane_x = 0;
    gen->plane_y = 0.66;
    gen->time = 0;
    gen->old_time = 0;
	gen->scale = 0;
	gen->size_line = 0;
	gen->map_height = 0;
	gen->map_width = 0;
	gen->window = 0;
	gen->map = NULL;
}

int				main(int argc, char **argv)
{
	t_gen	gen;
	int		fd;

	if (argc != 2)
	{
		ft_printf("{green}%s{reset}\n", "Usage: ./fdf <target file>");
		exit(0);
	}
	inicialization(&gen);
	fd = open(argv[1], O_RDONLY);
	reader(&gen, fd);
	gen.init = mlx_init();
	gen.window = mlx_new_window(gen.init, WINDOW_X, WINDOW_Y, "Wolf3d");
	gen.image = mlx_new_image(gen.init, WINDOW_X, WINDOW_Y);
	print_in_window(&gen);
	mlx_hook(gen.window, 2, 5, manage_keys, &gen);
	mlx_hook(gen.window, 17, 1L << 17, exit_x, &gen);
	mlx_loop(gen.init);
}
