/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:11:24 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:11:27 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	check_add(t_gen *gen, int i)
{
	int	j;

	j = 0;
	while (ft_isdigit(gen->array[i][j]) || gen->array[i][j] == '-')
		j++;
	if (ft_isdigit(gen->array[i][j]) == 0)
	{
		if (ft_strncmp(gen->array[i] + j, ",0x", 3) != 0)
		{
			ft_printf("{red}%s{reset}\n", "Error! Wrong color format!");
			exit_x(gen);
		}
		else
			j += 3;
		if (is_hexa(gen->array[i] + j) == 0)
		{
			ft_printf("{red}%s{reset}\n", "Error! Wrong color!");
			exit_x(gen);
		}
		else
			j += 6;
	}
}

void			check_colors(t_gen *gen)
{
	int	i;
	int	j;

	i = 0;
	while (gen->array[i])
	{
		j = 0;
		if (is_valid_data(gen->array[i]) == 0)
		{
			ft_printf("{red}%s{reset}\n", "Error! Wrong characters!");
			exit_x(gen);
		}
		if (ft_isdigit(gen->array[i][j]) == 0 && gen->array[i][j] != '-')
		{
			ft_printf("{red}%s{reset}\n",
				"Error! There is no coordinate before color!");
			exit_x(gen);
		}
		if (ft_strstr(gen->array[i], ",") || is_let(gen->array[i]))
			check_add(gen, i);
		i++;
	}
}
