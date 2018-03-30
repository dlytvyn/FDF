/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:13:23 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:13:24 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_scale(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	minus_coor(gen);
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
	plus_coor(gen);
	gen->scale = 1;
}

void	get_scale(t_gen *gen)
{
	if (WINDOW_X - gen->max_x < WINDOW_Y - gen->max_y)
		gen->scale = WINDOW_X / gen->max_x;
	else
		gen->scale = WINDOW_Y / gen->max_y;
	gen->scale = (gen->scale / 100) * SCALE;
	ft_scale(gen);
}
