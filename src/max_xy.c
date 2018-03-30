/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_xy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:12:25 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:12:26 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	max_xy(t_gen *gen)
{
	int	i;
	int	j;

	i = 0;
	gen->min_x = gen->list[0][0].x;
	gen->min_y = gen->list[0][0].y;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			if (gen->list[i][j].x > gen->max_x)
				gen->max_x = gen->list[i][j].x;
			if (gen->list[i][j].y > gen->max_y)
				gen->max_y = gen->list[i][j].y;
			if (gen->list[i][j].x < gen->min_x)
				gen->min_x = gen->list[i][j].x;
			if (gen->list[i][j].y < gen->min_y)
				gen->min_y = gen->list[i][j].y;
			j++;
		}
		i++;
	}
}
