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

#include "wolf3d.h"

void	print_in_window(t_gen *gen)
{
//	int	i;
//	int	j;
//
//	gen->field = (int*)mlx_get_data_addr(gen->image, &gen->bits_per_pixel,
//		&gen->size_line, &gen->endian);
//	i = 0;
//	while (i < gen->map_height)
//	{
//		j = 0;
//		while (j < gen->map_width)
//		{
//			if (i + 1 < gen->map_height)
//				line(gen, gen->list[i][j], gen->list[i + 1][j]);
//			if (j + 1 < gen->map_width)
//				line(gen, gen->list[i][j], gen->list[i][j + 1]);
//			j++;
//		}
//		i++;
//	}
//	mlx_put_image_to_window(gen->init, gen->window, gen->image, 0, 0);
//	show_str(gen);
}
