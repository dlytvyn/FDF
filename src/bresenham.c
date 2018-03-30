/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:10:34 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:10:45 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	put_pixel(int x, int y, t_gen *gen, int color)
{
	int i;

	if (x >= gen->size_line / 4 || x < 0 || y < 0)
		return ;
	i = (x + (y * (gen->size_line / 4)));
	gen->field[i] = color;
}

static	int		ft_incline(t_fdf t1, t_fdf t2)
{
	return (fabs(t2.y - t1.y) > fabs(t2.x - t1.x));
}

static	void	ft_swap(t_fdf *t1, t_fdf *t2, int i)
{
	double	tmp;

	if (i == 1)
	{
		tmp = t1->x;
		t1->x = t1->y;
		t1->y = tmp;
		tmp = t2->x;
		t2->x = t2->y;
		t2->y = tmp;
	}
	else
	{
		tmp = t1->x;
		t1->x = t2->x;
		t2->x = tmp;
		tmp = t1->y;
		t1->y = t2->y;
		t2->y = tmp;
		tmp = (double)t1->color;
		t1->color = t2->color;
		t2->color = (int)tmp;
	}
}

void			line(t_gen *gen, t_fdf t1, t_fdf t2)
{
	double dx;
	double dy;
	double steep;
	double err;
	double ystep;

	if ((steep = ft_incline(t1, t2)))
		ft_swap(&t1, &t2, 1);
	if (t1.x > t2.x)
		ft_swap(&t1, &t2, 0);
	dx = t2.x - t1.x;
	dy = fabs(t2.y - t1.y);
	err = dx / 2;
	ystep = (t1.y < t2.y) ? 1 : -1;
	while (t1.x++ < t2.x)
	{
		put_pixel(steep ? t1.y : t1.x, steep ? t1.x : t1.y, gen, t1.color);
		err -= dy;
		if (err < 0)
		{
			t1.y += ystep;
			err += dx;
		}
	}
}
