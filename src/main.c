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

#include "fdf.h"

void			clear(t_gen *gen)
{
	ft_bzero(gen->field, WINDOW_X * WINDOW_Y * 4);
	gen->size_line = 0;
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}

void			inicialization(t_gen *gen)
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
	gen->w_h = 1;
	gen->w_w = 0;
	gen->window = 0;
	gen->deg_x = -35 * M_PI / 180;
	gen->deg_y = -40 * M_PI / 180;
	gen->deg_z = 25 * M_PI / 180;
	gen->flag = 0;
	gen->color_index = 0;
	gen->list = NULL;
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
	get_scale(&gen);
	gen.init = mlx_init();
	gen.window = mlx_new_window(gen.init, WINDOW_X, WINDOW_Y, "FDF Project!");
	gen.image = mlx_new_image(gen.init, WINDOW_X, WINDOW_Y);
	rotate_matrix(&gen, 0);
	centering(&gen);
	print_in_window(&gen);
	mlx_hook(gen.window, 2, 5, manage_keys, &gen);
	mlx_hook(gen.window, 17, 1L << 17, exit_x, &gen);
	mlx_loop(gen.init);
}
