//
// Created by Dmytro LYTVYN on 3/20/18.
//

#include "fdf.h"

void    rotate_along_x(t_gen *gen)
{
	double radians;

	radians = gen->angle_x * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->y = gen->list->y * cos(radians) + gen->list->row->z * sin(radians);
			gen->list->row->z = -gen->list->y * sin(radians) + gen->list->row->z * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_along_y(t_gen *gen)
{
	double radians;

	radians = gen->angle_y * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x = gen->list->row->x * cos(radians) + gen->list->row->z * sin(radians);
			gen->list->row->z = -gen->list->row->x * sin(radians) + gen->list->row->z * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_along_z(t_gen *gen)
{
	double radians;

	radians = gen->angle_z * M_PI / 180;
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x = gen->list->row->x * cos(radians) - gen->list->y * sin(radians);
			gen->list->y = gen->list->row->x * sin(radians) + gen->list->y * cos(radians);
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    rotate_matrix(t_gen *gen)
{
	rotate_along_x(gen);
	rotate_along_y(gen);
	rotate_along_z(gen);
}
