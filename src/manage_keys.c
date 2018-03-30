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
}

int				manage_keys(int key, t_gen *gen)
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
	manage_add(key, gen);
	ft_scale(gen);
	rotate_matrix(gen, key);
	mlx_clear_window(gen->init, gen->window);
	clear(gen);
	print_in_window(gen);
	return (0);
}
