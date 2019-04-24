///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   change_coordinates.c                               :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2018/03/30 12:11:09 by dlytvyn           #+#    #+#             */
///*   Updated: 2018/03/30 12:11:12 by dlytvyn          ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */
//
//#include "fdf.h"
//
//void	minus_coor(t_gen *gen)
//{
//	int	i;
//	int	j;
//
//	max_xy(gen);
//	gen->diff_x = gen->list[gen->w_h / 2][gen->w_w / 2].x;
//	gen->diff_y = gen->list[gen->w_h / 2][gen->w_w / 2].y;
//	i = 0;
//	while (i < gen->w_h)
//	{
//		j = 0;
//		while (j < gen->w_w)
//		{
//			gen->list[i][j].x -= gen->diff_x;
//			gen->list[i][j].y -= gen->diff_y;
//			j++;
//		}
//		i++;
//	}
//}
//
//void	plus_coor(t_gen *gen)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < gen->w_h)
//	{
//		j = 0;
//		while (j < gen->w_w)
//		{
//			gen->list[i][j].x += gen->diff_x;
//			gen->list[i][j].y += gen->diff_y;
//			j++;
//		}
//		i++;
//	}
//}
//
//void	increase(t_gen *gen, int a)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < gen->w_h)
//	{
//		j = 0;
//		while (j < gen->w_w)
//		{
//			gen->list[i][j].z += a;
//			j++;
//		}
//		i++;
//	}
//}
