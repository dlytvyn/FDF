/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:10:56 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:10:59 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	centering(t_gen *gen)
{
	int	x;
	int	y;
	int	i;
	int	j;

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
