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



void    rotate_along_x(t_gen *gen)
{
	double	radians;
	int		or;

	radians = gen->angle_x * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			or = gen->list->y;
			gen->list->y = gen->list->y * cos(radians) + gen->list->row->z * sin(radians);
			gen->list->row->z = -or * sin(radians) + gen->list->row->z * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_along_y(t_gen *gen)
{
	double	radians;
	int		or;

	radians = gen->angle_y * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			or = gen->list->row->x;
			gen->list->row->x = (gen->list->row->x * cos(radians) + gen->list->row->z * sin(radians));
			gen->list->row->z = -or * sin(radians) + gen->list->row->z * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_along_z(t_gen *gen)
{
	double	radians;
	int		or;

	radians = gen->angle_z * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			or = gen->list->row->x;
			gen->list->row->x = gen->list->row->x * cos(radians) - gen->list->y * sin(radians);
			gen->list->y = or * sin(radians) + gen->list->y * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_matrix(t_gen *gen, int key)
{
	if (key == 7)
		rotate_along_x(gen);
	else if (key == 16)
		rotate_along_y(gen);
	else if (key == 6)
		rotate_along_z(gen);
	//centering(gen);
}
