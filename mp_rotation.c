//
// Created by Dmytro LYTVYN on 3/20/18.
//

#include "fdf.h"

void	increase(t_gen *gen,int a)
{
	int 	i;
	int		j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].z += a;
			j++;
		}
		i++;
	}
}

void    rotate_along_x(t_gen *gen)
{
	int 	i;
	int		j;
	int		or;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			or = gen->list[i][j].y;
			gen->list[i][j].y = gen->list[i][j].y * cos(gen->deg_x) + gen->list[i][j].z * sin(gen->deg_x);
			gen->list[i][j].z = -or * sin(gen->deg_x) + gen->list[i][j].z * cos(gen->deg_x);
			j++;
		}
		i++;
	}
	gen->deg_x = 0;
}

void    rotate_along_y(t_gen *gen)
{
	int 	i;
	int		j;
	int		or;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			or = gen->list[i][j].x;
			gen->list[i][j].x = (gen->list[i][j].x * cos(gen->deg_y) + gen->list[i][j].z * sin(gen->deg_y));
			gen->list[i][j].z = -or * sin(gen->deg_y) + gen->list[i][j].z * cos(gen->deg_y);
			j++;
		}
		i++;
	}
	gen->deg_y = 0;
}

void    rotate_along_z(t_gen *gen)
{
	int 	i;
	int		j;
	int		or;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			or = gen->list[i][j].x;
			gen->list[i][j].x = gen->list[i][j].x * cos(gen->deg_z) - gen->list[i][j].y * sin(gen->deg_z);
			gen->list[i][j].y = or * sin(gen->deg_z) + gen->list[i][j].y * cos(gen->deg_z);
			j++;
		}
		i++;
	}
	gen->deg_z = 0;
}

// void	rotation(t_gen *gen, int a, int b, int c)
// {
// 	double 	x;
// 	double 	y;
// 	double 	z;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < gen->w_h)
// 	{
// 		j = 0;
// 		while (j < gen->w_w)
// 		{
// 			x = gen->list[i][j].x;
//         	y = gen->list[i][j].y;
//         	z = gen->list[i][j].z;
//         	gen->list[i][j].x = x * (cos(gen->deg) + (1 - cos(gen->deg)) * a * a) + y * ((1 - cos(gen->deg)) * a * b + sin(gen->deg) * c) + z * ((1 - cos(gen->deg)) * a * c - sin(gen->deg) * b);
//         	gen->list[i][j].y = x * ((1 - cos(gen->deg)) * a * b  - sin(gen->deg) * c) + y * (cos(gen->deg) + (1 - cos(gen->deg)) * b * b) + z * ((1 - cos(gen->deg)) * b * c + sin(gen->deg) * a);
//         	gen->list[i][j].z = x * ((1 - cos(gen->deg)) * a * c + sin(gen->deg) * b) + y * ((1 - cos(gen->deg)) * b * c - sin(gen->deg) * a) + z * ((1 - cos(gen->deg)) * c * c + cos(gen->deg));
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	minus_coor(t_gen *gen)
{
	int i;
	int j;
	max_xy(gen);
	gen->diff_x = (gen->max_x + gen->min_x) / 2; 
	gen->diff_y = (gen->max_y + gen->min_y) / 2;
	i = 0;
	while (i < gen->w_h)
	 {
		 j = 0;
		 while (j < gen->w_w)
		 {
			 gen->list[i][j].x -= gen->diff_x;
			 gen->list[i][j].y -= gen->diff_y;
			 j++;
		 }
		 i++;
	 }
}

void	plus_coor(t_gen *gen)
{
	int i;
	int j;

	i = 0;
	while (i < gen->w_h)
	{
		j = 0;
		while (j < gen->w_w)
		{
			gen->list[i][j].x += gen->diff_x;
			gen->list[i][j].y += gen->diff_y;
			j++;
		}
		i++;
	}
}

void    rotate_matrix(t_gen *gen, int key)
{
	if (key == 7 || key == 16 || key == 6 || key == 116 || key == 121)
	{
		minus_coor(gen);
		// rotation(gen, 1, 0 , 0);
		// rotation(gen, 0, 1, 0);
		// rotation(gen, 0, 0, 1);
		rotate_along_x(gen);
		rotate_along_y(gen);
		rotate_along_z(gen);
		plus_coor(gen);
	}
	//centering(gen);
}
