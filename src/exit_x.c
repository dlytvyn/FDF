/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:59:09 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/05/07 13:59:30 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			free_struct(t_gen *gen)
{
	int i;

	i = 0;
	if (!gen->map)
		return ;
	while (i < gen->map_height)
	{
		free(gen->map[i]);
		i++;
	}
	free(gen->map);
	gen->map = NULL;
}

void			free_array(char **array)
{
	int i;

	i = 0;
	if (array[0] == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int				exit_x(t_gen *gen)
{
	free_array(gen->array);
	free_struct(gen);
	exit(0);
}
