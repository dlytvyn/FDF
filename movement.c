//
// Created by Dmytro LYTVYN on 3/21/18.
//

#include "fdf.h"

void    move_to_right(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x += 7;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    move_to_left(t_gen *gen)
{
	while (gen->list)
	{
		while (gen->list->row)
		{
			gen->list->row->x -=7;
			gen->list->row = gen->list->row->next;
		}
		gen->list->row = gen->list->clone;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    move_up(t_gen *gen)
{
	while (gen->list)
	{
		gen->list->y -= 7;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}

void    move_down(t_gen *gen)
{
	while (gen->list)
	{
		gen->list->y += 7;
		gen->list = gen->list->next;
	}
	gen->list = gen->run;
}
