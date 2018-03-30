/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_in_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:13:04 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:13:05 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_in_window(t_gen *gen)
{
	int	i;
	int	j;

	gen->field = (int*)mlx_get_data_addr(gen->image, &gen->bits_per_pixel,
		&gen->size_line, &gen->endian);
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
	mlx_string_put(gen->init, gen->window, 100, 100, 16777215, "Welcome to FDF");
	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
}
