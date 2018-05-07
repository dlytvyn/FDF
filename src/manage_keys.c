/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:12:14 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:12:14 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			show_str(t_gen *gen)
{
	if (!gen->flag)
		mlx_string_put(gen->init, gen->window, 20, 20, 0x00FF00,
			"Press Enter to see useful buttons!");
	else
	{
		mlx_string_put(gen->init, gen->window, 20, 20, 0x0000FF,
			"Rotation along x-axis: X and C");
		mlx_string_put(gen->init, gen->window, 20, 40, 0x0000FF,
			"Rotation along y-axis: Y and T");
		mlx_string_put(gen->init, gen->window, 20, 60, 0x0000FF,
			"Rotation along z-axis: Z and A");
		mlx_string_put(gen->init, gen->window, 20, 80, 0x0000FF,
			"Zoom in/out: + and -");
		mlx_string_put(gen->init, gen->window, 20, 100, 0x0000FF,
			"Movement: arrows");
		mlx_string_put(gen->init, gen->window, 20, 120, 0x0000FF,
			"Change default colors: W");
		mlx_string_put(gen->init, gen->window, 20, 140, 0x0000FF,
			"Change all colors: E");
		mlx_string_put(gen->init, gen->window, 20, 160, 0x0000FF,
			"Hide this menu: Q");
		mlx_string_put(gen->init, gen->window, 20, 180, 0x0000FF, "Exit: Esc");
		gen->flag = 1;
	}
}

static	void	manage_add(int key, t_gen *gen)
{
	if (key == 116)
		increase(gen, 10);
	else if (key == 121)
		increase(gen, -10);
	else if (key == 123)
		move_to_left(gen);
	else if (key == 124)
		move_to_right(gen);
	else if (key == 126)
		move_up(gen);
	else if (key == 125)
		move_down(gen);
	else if (key == 69)
		gen->scale = 1.1;
	else if (key == 78)
		gen->scale = 0.9;
	else if (key == 36)
		gen->flag = 1;
	else if (key == 12)
		gen->flag = 0;
}

void			cycle(t_gen *gen, int color, int key)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			if (gen->list[i][j].in == 0 && key == 13)
				gen->list[i][j].color = color;
			else if (key == 14)
				gen->list[i][j].color = color;
			j++;
		}
		i++;
	}
}

void			change_color(t_gen *gen, int key)
{
	if (gen->color_index == 0)
		cycle(gen, 16318208, key);
	else if (gen->color_index == 1)
		cycle(gen, 2752256, key);
	else if (gen->color_index == 2)
		cycle(gen, 65525, key);
	else if (gen->color_index == 3)
		cycle(gen, 14079, key);
	else if (gen->color_index == 4)
		cycle(gen, 16711891, key);
	else if (gen->color_index == 5)
		cycle(gen, 16749312, key);
	else if (gen->color_index == 6)
		cycle(gen, 162610, key);
	else if (gen->color_index == 7)
		cycle(gen, 16777215, key);
	else if (gen->color_index == 8)
		cycle(gen, 16449536, key);
	gen->color_index++;
	if (gen->color_index > 8)
		gen->color_index = 0;
}

int				manage_keys(int key, t_gen *gen)
{
	if (key == 53)
		exit_x(gen);
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
	else if (key == 13)
		change_color(gen, key);
	else if (key == 14)
		change_color(gen, key);
	manage_add(key, gen);
	ft_scale(gen);
	rotate_matrix(gen, key);
	mlx_clear_window(gen->init, gen->window);
	clear(gen);
	print_in_window(gen);
	return (0);
}
