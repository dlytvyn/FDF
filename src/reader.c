/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlytvyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 12:13:15 by dlytvyn           #+#    #+#             */
/*   Updated: 2018/03/30 12:13:16 by dlytvyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	add(int i, int j, int k, t_gen *gen)
{
	int	l;

	l = 0;
	if (ft_strstr(gen->array[k], ",0x"))
	{
		while (gen->array[k][l] != 'x')
			l++;
		l++;
		gen->list[i][j].color = ft_atoi_base(gen->array[k] + l, 16);
		gen->list[i][j].in = 1;
	}
	else
	{
		gen->list[i][j].color = 16449536;
		gen->list[i][j].in = 0;
	}
}

static	void	separate_add(t_gen *gen)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < gen->w_h)
	{
		j = 0;
		gen->list[i] = (t_fdf*)malloc(sizeof(t_fdf) * gen->w_w);
		while (j < gen->w_w)
		{
			gen->list[i][j].x = j;
			gen->list[i][j].y = i;
			add(i, j, k, gen);
			gen->list[i][j].z = ft_atoi(gen->array[k]);
			++k && ++j;
		}
		i++;
	}
}

static	void	separate_data(t_gen *gen)
{
	gen->array = ft_strsplit(gen->buf, ' ');
	ft_strdel(&gen->buf);
	check_colors(gen);
	if (gen->w_h * gen->w_w != array_len(gen->array))
	{
		ft_printf("{red}%s{reset}\n", "Found wrong line length. Exiting.");
		exit_x(gen);
	}
	else if (array_len(gen->array) == 0)
	{
		ft_printf("{red}%s{reset}\n", "Error! No map found!");
		exit_x(gen);
	}
	gen->list = (t_fdf**)malloc(sizeof(t_fdf*) * gen->w_h);
	separate_add(gen);
	gen->max_x = gen->w_w - 1;
	gen->max_y = gen->w_h - 1;
}

static	void	go_out(void)
{
	ft_printf("{red}%s{reset}\n", "Error! There is no file ot empty file!");
	exit(0);
}

void			reader(t_gen *gen, int fd)
{
	char	*tmp;
	char	*line;
	char	**array;

	if (get_next_line(fd, &line) <= 0)
		go_out();
	gen->buf = ft_strdup(line);
	array = ft_strsplit(line, ' ');
	ft_strdel(&line);
	gen->w_w = array_len(array);
	free_array(array);
	while (get_next_line(fd, &line))
	{
		tmp = ft_strdup(gen->buf);
		ft_strdel(&gen->buf);
		gen->buf = ft_strjoin(tmp, " ");
		ft_strdel(&tmp);
		tmp = ft_strdup(gen->buf);
		ft_strdel(&gen->buf);
		gen->buf = ft_strjoin(tmp, line);
		ft_strdel(&tmp);
		ft_strdel(&line);
		gen->w_h++;
	}
	separate_data(gen);
}
