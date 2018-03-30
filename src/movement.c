/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:12:38 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:12:41 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_to_right(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].x += 12;
			j++;
		}
		i++;
	}
}

void	move_to_left(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].x -= 12;
			j++;
		}
		i++;
	}
}

void	move_up(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].y -= 12;
			j++;
		}
		i++;
	}
}

void	move_down(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].y += 12;
			j++;
		}
		i++;
	}
}
