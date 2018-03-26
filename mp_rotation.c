//
// Created by Dmytro LYTVYN on 3/20/18.
//

#include "fdf.h"

void	increase(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->z += 2;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void	decrease(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->z -= 2;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}



// void    rotate_along_x(t_gen *gen)
// {
// 	double	radians;
// 	int		or;

// 	radians = gen->angle_x * M_PI / 180;
// 	while (gen->list)
// 	{
// 		while (gen->list->row)
// 		{
// 			or = gen->list->y;
// 			gen->list->y = gen->list->y * cos(radians) + gen->list->row->z * sin(radians);
// 			gen->list->row->z = -or * sin(radians) + gen->list->row->z * cos(radians);
// 			gen->list->row = gen->list->row->next;
// 		}
// 		gen->list->row = gen->list->clone;
// 		gen->list = gen->list->next;
// 	}
// 	gen->list = gen->run;
// }

// void    rotate_along_y(t_gen *gen)
// {
// 	double	radians;
// 	int		or;

// 	radians = gen->angle_y * M_PI / 180;
// 	while (gen->list)
// 	{
// 		while (gen->list->row)
// 		{
// 			or = gen->list->row->x;
// 			gen->list->row->x = (gen->list->row->x * cos(radians) + gen->list->row->z * sin(radians));
// 			gen->list->row->z = -or * sin(radians) + gen->list->row->z * cos(radians);
// 			gen->list->row = gen->list->row->next;
// 		}
// 		gen->list->row = gen->list->clone;
// 		gen->list = gen->list->next;
// 	}
// 	gen->list = gen->run;
// }

// void    rotate_along_z(t_gen *gen)
// {
// 	double	radians;
// 	int		or;

// 	radians = gen->angle_z * M_PI / 180;
// 	while (gen->list)
// 	{
// 		while (gen->list->row)
// 		{
// 			or = gen->list->row->x;
// 			gen->list->row->x = gen->list->row->x * cos(radians) - gen->list->y * sin(radians);
// 			gen->list->y = or * sin(radians) + gen->list->y * cos(radians);
// 			gen->list->row = gen->list->row->next;
// 		}
// 		gen->list->row = gen->list->clone;
// 		gen->list = gen->list->next;
// 	}
// 	gen->list = gen->run;
// }

void	rotation(t_gen *gen, int a, int b, int c, int key)
{
	double	deg;
	double x;
	double y;
	double z;

	if (key == 6)
		deg = gen->angle_z * M_PI / 180;
	else if (key == 7)
		deg = gen->angle_x * M_PI / 180;
	else if (key == 16)
		deg = gen->angle_y * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			 printf("Before x: %f\n", gen->list->row->x);
			 printf("Before y: %f\n", gen->list->y); 
			 printf("Before z: %f\n", gen->list->row->z);
			x = gen->list->row->x;
        	y = gen->list->y;
        	z = gen->list->row->z;
        	gen->list->row->x = x * (cos(deg) + (1 - cos(deg)) * a * a) + y * ((1 - cos(deg)) * a * b + sin(deg) * c) + z * ((1 - cos(deg)) * a * c - sin(deg) * b);
        	gen->list->y = x * ((1 - cos(deg)) * a * b  - sin(deg) * c) + y * (cos(deg) + (1 - cos(deg)) * b * b) + z * ((1 - cos(deg)) * b * c + sin(deg) * a);
        	gen->list->row->z = x * ((1 - cos(deg)) * a * c + sin(deg) * b) + y * ((1 - cos(deg)) * b * c - sin(deg) * a) + z * ((1 - cos(deg)) * c * c + cos(deg));
			printf("After x: %f\n", gen->list->row->x);
			printf("After y: %f\n", gen->list->y);
			printf("After z: %f\n", gen->list->row->z);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void	minus_coor(t_gen *gen)
{
	gen->diff_x = gen->list->row->x;
	gen->diff_y = gen->list->y;
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x -= gen->diff_x;
			gen->list->row = gen->list->row->next;
		}
		gen->list->y -= gen->diff_y;
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void	plus_coor(t_gen *gen)
{
	gen->diff_x = gen->list->row->x;
	gen->diff_y = gen->list->y;
	while (gen->list)
	{
		//printf("ffffffffffff\n");
		while (gen->list->row)
		{
			gen->list->row->x += gen->diff_x;
			gen->list->row = gen->list->row->next;
		}
		gen->list->y += gen->diff_y;
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_matrix(t_gen *gen, int key)
{
	if (key == 7 || key == 16 || key == 6)
	{
		//minus_coor(gen);
		if (key == 7)
			rotation(gen, 1, 0 , 0, key);
		else if (key == 16)
			rotation(gen, 0, 1, 0, key);
		else if (key == 6)
			rotation(gen, 0, 0, 1, key);
		//plus_coor(gen);
	}
	//centering(gen);
}
